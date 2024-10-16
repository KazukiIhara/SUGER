#include "Particle.h"
#include <sstream>
#include <fstream>
#include <cassert>

#include "framework/SUGER.h"
#include "math/function/MathFunction.h"


void cParticleSystem::Initialize(Matrix4x4* viewProjection, sUVTransform* uvTransform) {

	// 乱数生成器の初期化
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());

	// エミッターのトランフォーム設定
	emitter_.transform.translate = { 0.0f,0.0f,0.0f };
	emitter_.transform.rotate = { 0.0f,0.0f,0.0f };
	emitter_.transform.scale = { 1.0f,1.0f,1.0f };

	/*NullCheck*/
	assert(uvTransform);
	assert(viewProjection);

#pragma region Instancing
	// Instancingリソースを作る
	CreateInstancingResource();
	// Instancingデータを書き込む
	MapInstancingData();

#pragma endregion

	CreateSRV();
}

void cParticleSystem::Update(const Matrix4x4& cameraMatrix) {
	// 乱数を使う準備
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());

	// エミッターの処理
	// 時刻を進める
	emitter_.frequencyTime += kDeltaTime;

	// 頻度より大きいなら発生
	if (emitter_.frequency <= emitter_.frequencyTime) {
		// 発生処理
		particles_.splice(particles_.end(), Emit(emitter_, randomEngine));
		// 余計に過ぎた時間も加味して頻度計算する
		emitter_.frequencyTime -= emitter_.frequency;
	}

	// 描画すべきインスタンス数
	instanceCount_ = 0;

	for (std::list<Particle>::iterator particleIterator = particles_.begin();
		particleIterator != particles_.end();) {
		// 生存時間を過ぎていたら更新せず描画対象にしない
		if ((*particleIterator).lifeTime <= (*particleIterator).currentTime) {
			particleIterator = particles_.erase(particleIterator);
			continue;
		}


		// 経過時間を足す
		(*particleIterator).currentTime += kDeltaTime;
		// 移動
		(*particleIterator).transform.translate += kDeltaTime * (*particleIterator).velocity;
		// 透明度
		float alpha = 1.0f - ((*particleIterator).currentTime / (*particleIterator).lifeTime);

		if (instanceCount_ < kNumMaxInstance) {
			// 180度回す回転行列を作成する
			Matrix4x4 backFrontMatrix = MakeRotateYMatrix(std::numbers::pi_v<float>);

			// WVPマトリックスを求める
			Matrix4x4 scaleMatrix = MakeScaleMatrix((*particleIterator).transform.scale);
			Matrix4x4 billboardMatrix = backFrontMatrix * cameraMatrix;
			// 平行移動成分を削除
			billboardMatrix.m[3][0] = 0.0f;
			billboardMatrix.m[3][1] = 0.0f;
			billboardMatrix.m[3][2] = 0.0f;

			Matrix4x4 translateMatrix = MakeTranslateMatrix((*particleIterator).transform.translate);

			if (!isUseBillboard) {
				billboardMatrix = MakeIdentityMatrix4x4();
			}

			Matrix4x4 worldMatrix = scaleMatrix * billboardMatrix * translateMatrix;

			Matrix4x4 worldViewProjectionMatrix = worldMatrix * *viewProjection_;

			instancingData_[instanceCount_].WVP = worldViewProjectionMatrix;
			instancingData_[instanceCount_].World = worldMatrix;
			// 色を入力
			instancingData_[instanceCount_].color.x = (*particleIterator).color.x;
			instancingData_[instanceCount_].color.y = (*particleIterator).color.y;
			instancingData_[instanceCount_].color.z = (*particleIterator).color.z;
			instancingData_[instanceCount_].color.w = alpha;

			// 生きているParticleの数を1つカウントする
			instanceCount_++;
		}
		// 次のイテレーターに進める
		++particleIterator;
	}

	// 色を書き込む
	materialData_->color = modelData_.material.color;



}

void cParticleSystem::Draw(uint32_t textureHandle, BlendMode blendMode) {
	// PSOを設定
	SUGER::GetDirectXCommandList()->SetPipelineState(SUGER::GetPipelineState(kObject3d, blendMode));
	//VBVを設定
	SUGER::GetDirectXCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	/*マテリアルCBufferの場所を設定*/
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	// StructuredBufferのSRVを設定する
	SUGER::GetDirectXCommandList()->SetGraphicsRootDescriptorTable(1, instancingSrvHandleGPU);
	/*SRVのDescriptorTableの先頭を設定*/
	SUGER::GetDirectXCommandList()->SetGraphicsRootDescriptorTable(2, SUGER::GetTexture()[].gpuDescHandleSRV);
	//描画！(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	SUGER::GetDirectXCommandList()->DrawInstanced(6, instanceCount_, 0, 0);
}

void cParticleSystem::CreateInstancingResource() {
	// instancing用のリソースを作る
	instancingResource_ = SUGER::CreateBufferResource(sizeof(ParticleForGPU) * kNumMaxInstance);
}

void cParticleSystem::MapInstancingData() {
	instancingData_ = nullptr;
	instancingResource_->Map(0, nullptr, reinterpret_cast<void**>(&instancingData_));

	for (uint32_t index = 0; index < kNumMaxInstance; ++index) {

		instancingData_[index].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

Particle cParticleSystem::MakeNewParticle(std::mt19937& randomEngine, const Vector3& translate) {
	// 出現位置と移動量の乱数の生成
	std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
	// 色を決める乱数の生成
	std::uniform_real_distribution<float> distColor(0.0f, 1.0f);
	// 生存時間の乱数の生成(1秒から3秒の間生存)
	std::uniform_real_distribution<float> distTime(1.0f, 3.0f);

	Particle particle;
	// トランスフォームの設定
	particle.transform.scale = { 1.0f,1.0f,1.0f };
	particle.transform.rotate = { 0.0f,0.0f,0.0f };

	Vector3 randomTranslate{ distribution(randomEngine), distribution(randomEngine), distribution(randomEngine) };
	// 位置と移動量を[-1,1]の範囲でランダムに初期化
	particle.transform.translate = translate + randomTranslate;
	// 移動量の設定
	particle.velocity = { distribution(randomEngine), distribution(randomEngine), distribution(randomEngine) };
	// 色の設定
	particle.color = { distribution(randomEngine), distribution(randomEngine), distribution(randomEngine),1.0f };

	// 生存時間の設定
	particle.lifeTime = distTime(randomEngine);
	particle.currentTime = 0;

	return particle;
}

void cParticleSystem::CreateSRV() {
	D3D12_SHADER_RESOURCE_VIEW_DESC instancingSrvDesc{};
	instancingSrvDesc.Format = DXGI_FORMAT_UNKNOWN;
	instancingSrvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	instancingSrvDesc.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
	instancingSrvDesc.Buffer.FirstElement = 0;
	instancingSrvDesc.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
	instancingSrvDesc.Buffer.NumElements = kNumMaxInstance;
	instancingSrvDesc.Buffer.StructureByteStride = sizeof(ParticleForGPU);
	D3D12_CPU_DESCRIPTOR_HANDLE instancingSrvHandleCPU = cDirectXCommon::GetCPUDescriptorHandle(cDirectXCommon::GetSRVDescriptorHeap(), cDirectXCommon::GetDescriptorSizeSRV(), 1);
	instancingSrvHandleGPU = cDirectXCommon::GetGPUDescriptorHandle(cDirectXCommon::GetSRVDescriptorHeap(), cDirectXCommon::GetDescriptorSizeSRV(), 1);
	cDirectXCommon::GetDevice()->CreateShaderResourceView(instancingResource_.Get(), &instancingSrvDesc, instancingSrvHandleCPU);
}

std::list<Particle> cParticleSystem::Emit(const Emitter& emitter, std::mt19937& randomEngine) {
	std::list<Particle> particles;
	for (uint32_t count = 0; count < emitter.count; ++count) {
		particles.push_back(MakeNewParticle(randomEngine, emitter.transform.translate));
	}
	return particles;
}
