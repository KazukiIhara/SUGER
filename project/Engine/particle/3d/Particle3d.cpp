#include "Particle3d.h"
#include <sstream>
#include <fstream>
#include <cassert>

#include "framework/SUGER.h"
#include "math/function/MathFunction.h"
#include "3d/model/Model.h"
#include "3d/cameras/camera/Camera.h"


void Particle3D::Initialize(Model* model, Camera* camera) {
	// インスタンスをセット
	SetModel(model);
	SetCamera(camera);

	// 乱数生成器の初期化
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());

	// エミッターのトランフォーム設定
	emitter_.transform.translate = { 0.0f,0.0f,0.0f };
	emitter_.transform.rotate = { 0.0f,0.0f,0.0f };
	emitter_.transform.scale = { 1.0f,1.0f,1.0f };

#pragma region Instancing
	// Instancingリソースを作る
	CreateInstancingResource();
	// Instancingデータを書き込む
	MapInstancingData();

#pragma endregion
	// srvのインデックスを割り当て
	srvIndex_ = SUGER::SrvAllocate();
	// Srvを作成
	SUGER::CreateSrvInstancing(srvIndex_, instancingResource_.Get(), kNumMaxInstance, sizeof(ParticleForGPU));
}

void Particle3D::Update() {
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

	for (std::list<ParticleData>::iterator particleIterator = particles_.begin();
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
			Matrix4x4 billboardMatrix = backFrontMatrix * camera_->GetWorldMatrix();
			// 平行移動成分を削除
			billboardMatrix.m[3][0] = 0.0f;
			billboardMatrix.m[3][1] = 0.0f;
			billboardMatrix.m[3][2] = 0.0f;

			Matrix4x4 translateMatrix = MakeTranslateMatrix((*particleIterator).transform.translate);

			// billboardMatrix = MakeIdentityMatrix4x4();

			Matrix4x4 worldMatrix = scaleMatrix * billboardMatrix * translateMatrix;

			Matrix4x4 worldViewProjectionMatrix = worldMatrix * camera_->GetViewProjectionMatrix();

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
}

void Particle3D::Draw(BlendMode blendMode) {
	// PSOを設定
	SUGER::GetDirectXCommandList()->SetPipelineState(SUGER::GetPipelineState(kParticle, blendMode));

	// StructuredBufferのSRVを設定する
	SUGER::GetDirectXCommandList()->SetGraphicsRootDescriptorTable(1, SUGER::GetSRVDescriptorHandleGPU(srvIndex_));

	// モデルがある場合描画
	if (model_) {
		model_->DrawParticle(instanceCount_);
	}
}

void Particle3D::SetModel(Model* model) {
	model_ = model;
}

void Particle3D::SetCamera(Camera* camera) {
	camera_ = camera;
}

void Particle3D::CreateInstancingResource() {
	// instancing用のリソースを作る
	instancingResource_ = SUGER::CreateBufferResource(sizeof(ParticleForGPU) * kNumMaxInstance);
}

void Particle3D::MapInstancingData() {
	instancingData_ = nullptr;
	instancingResource_->Map(0, nullptr, reinterpret_cast<void**>(&instancingData_));

	for (uint32_t index = 0; index < kNumMaxInstance; ++index) {

		instancingData_[index].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

ParticleData Particle3D::MakeNewParticle(std::mt19937& randomEngine, const Vector3& translate) {
	// 出現位置と移動量の乱数の生成
	std::uniform_real_distribution<float> distribution(-1.0f, 1.0f);
	// 色を決める乱数の生成
	std::uniform_real_distribution<float> distColor(0.0f, 1.0f);
	// 生存時間の乱数の生成(1秒から3秒の間生存)
	std::uniform_real_distribution<float> distTime(1.0f, 3.0f);

	ParticleData particle;
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

std::list<ParticleData> Particle3D::Emit(const Emitter& emitter, std::mt19937& randomEngine) {
	std::list<ParticleData> particles;
	for (uint32_t count = 0; count < emitter.count; ++count) {
		particles.push_back(MakeNewParticle(randomEngine, emitter.transform.translate));
	}
	return particles;
}
