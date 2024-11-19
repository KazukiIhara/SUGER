#include "RandomParticle.h"
#include <sstream>
#include <fstream>
#include <cassert>

#include "framework/SUGER.h"
#include "math/function/MathFunction.h"
#include "3d/model/Model.h"
#include "3d/cameras/camera/Camera.h"


void RandomParticle::Initialize(Model* model, Camera* camera, const std::string& textureFileName, const EulerTransform3D& transform) {
	// インスタンスをセット
	SetModel(model);
	SetCamera(camera);

	// 乱数生成器の初期化
	std::random_device seedGenerator;
	std::mt19937 randomEngine(seedGenerator());

	// テクスチャファイル名をセット
	textureFileName_ = textureFileName;

	// エミッターの設定
	emitter_.transform.scale = transform.scale;
	emitter_.transform.rotate = transform.rotate;
	emitter_.transform.translate = transform.translate;

	emitter_.count = 5;		// 一度に発生する数
	emitter_.frequency = 0.5f;	// 発生頻度
	emitter_.frequencyTime = 0.0f;	// 発生頻度用の時刻、0で初期化

	// マテリアル初期化
	material_.color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	material_.enableLighting = true;
	material_.shininess = 40.0f;
	material_.uvTransformMatrix = MakeIdentityMatrix4x4();

	// Instancingリソースを作る
	CreateInstancingResource();
	// Instancingデータを書き込む
	MapInstancingData();

	// マテリアルリソース作成
	CreateMaterialResource();
	// マテリアルデータ書き込み
	MapMaterialData();

	// srvのインデックスを割り当て
	srvIndex_ = SUGER::SrvAllocate();
	// Srvを作成
	SUGER::CreateSrvStructured(srvIndex_, instancingResource_.Get(), kNumMaxInstance, sizeof(ParticleForGPU));
}

void RandomParticle::Update() {
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

void RandomParticle::Draw(BlendMode blendMode) {
	// PSOを設定
	SUGER::GetDirectXCommandList()->SetPipelineState(SUGER::GetPipelineState(kParticle, blendMode));

	// StructuredBufferのSRVを設定する
	SUGER::GetDirectXCommandList()->SetGraphicsRootDescriptorTable(1, SUGER::GetSRVDescriptorHandleGPU(srvIndex_));
	// マテリアルCBufferの場所を設定
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	// モデルがある場合描画
	if (model_) {
		switch (type_) {
		case kPlane:
			model_->DrawPlaneParticle(instanceCount_, textureFileName_);
			break;
		}
	}
}

void RandomParticle::SetModel(Model* model) {
	model_ = model;
}

void RandomParticle::SetCamera(Camera* camera) {
	camera_ = camera;
}

void RandomParticle::SetType(ParticleType type) {
	type_ = type;
}

void RandomParticle::SetRotate(const Vector3& rotate) {
	emitter_.transform.rotate = rotate;
}

void RandomParticle::SetTranslate(const Vector3& translate) {
	emitter_.transform.translate = translate;
}

void RandomParticle::SetCount(const uint32_t& count) {
	emitter_.count = count;
}

void RandomParticle::SetIsActive(const bool& isActive) {
	isActive_ = isActive;
}

const bool& RandomParticle::GetIsActive() {
	return isActive_;
}

void RandomParticle::CreateInstancingResource() {
	// instancing用のリソースを作る
	instancingResource_ = SUGER::CreateBufferResource(sizeof(ParticleForGPU) * kNumMaxInstance);
}

void RandomParticle::MapInstancingData() {
	instancingData_ = nullptr;
	instancingResource_->Map(0, nullptr, reinterpret_cast<void**>(&instancingData_));

	for (uint32_t index = 0; index < kNumMaxInstance; ++index) {

		instancingData_[index].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

void RandomParticle::CreateMaterialResource() {
}

void RandomParticle::MapMaterialData() {
}

ParticleData RandomParticle::MakeNewParticle(std::mt19937& randomEngine, const Vector3& translate) {
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

std::list<ParticleData> RandomParticle::Emit(const Emitter& emitter, std::mt19937& randomEngine) {
	std::list<ParticleData> particles;
	for (uint32_t count = 0; count < emitter.count; ++count) {
		particles.push_back(MakeNewParticle(randomEngine, emitter.transform.translate));
	}
	return particles;
}
