#include "Emitter.h"

#include "framework/SUGER.h"
#include "random/Random.h"

void Emitter::Initialize() {
	// 基底クラスの初期化
	Empty::Initialize();

	// 発生設定の初期化
	// 発生数は1
	count_ = 1;
	// 座標は0,0,0
	emitParamater_.position = { 0.0f,0.0f,0.0f };
	// サイズは1.0
	emitParamater_.scale = { 1.0f,1.0f,1.0f };
	// 移動量は0
	emitParamater_.velocity = { 0.0f,0.0f,0.0f };
	// 色は白
	emitParamater_.color = { 1.0f,1.0f,1.0f,1.0f };
	// 生存時間をひとまず5秒に設定
	emitParamater_.lifeTime = 5.0f;
}

void Emitter::Update() {
	// 基底クラスの更新
	Empty::Update();

	// 繰り返しフラグがオンなら繰り返し発生
	if (isRepeat_) {

		// エミッターの処理
		// 時刻を進める
		frequencyTime_ += kDeltaTime_;

		// 頻度より大きいなら発生
		if (frequency_ <= frequencyTime_) {
			Emit();
			// 余計に過ぎた時間も加味して頻度計算する
			frequencyTime_ -= frequency_;
		}
	}
}

void Emitter::Emit() {
	// パーティクル発生ポジション
	Vector3 emitterPosition = GetWorldPosition();
	emitParamater_.position = emitterPosition;
	// ブレンドモードセット
	particle_->SetBlendMode(blendMode_);
	// 発生タイプごとの処理
	switch (emitType_) {
		// デフォルト
		case kDefault:
			// 発生個数分ループ
			for (uint32_t i = 0; i < count_; i++) {
				// サイズ
				float size = Random::GenerateFloat(minSize_, maxSize_);
				emitParamater_.scale.x = size;
				emitParamater_.scale.y = size;
				emitParamater_.scale.z = size;
				// 座標
				emitParamater_.position.x = emitterPosition.x + i * 0.1f;
				emitParamater_.position.y = emitterPosition.y + i * 0.1f;
				particle_->AddNewParticle(emitParamater_);
			}
			break;
			// ランダム 
		case kRandom:
			// 発生個数分ループ
			for (uint32_t i = 0; i < count_; i++) {
				// 発生座標
				emitParamater_.position.x = emitterPosition.x + Random::GenerateFloat(minTranslate_.x, maxTranslate_.x);
				emitParamater_.position.y = emitterPosition.y + Random::GenerateFloat(minTranslate_.y, maxTranslate_.y);
				emitParamater_.position.z = emitterPosition.z + Random::GenerateFloat(minTranslate_.z, maxTranslate_.z);
				// サイズ
				float size = Random::GenerateFloat(minSize_, maxSize_);
				emitParamater_.scale.x = size;
				emitParamater_.scale.y = size;
				emitParamater_.scale.z = size;
				// 移動量
				emitParamater_.velocity.x = Random::GenerateFloat(minVelocity_.x, maxVelocity_.x);
				emitParamater_.velocity.y = Random::GenerateFloat(minVelocity_.y, maxVelocity_.y);
				emitParamater_.velocity.z = Random::GenerateFloat(minVelocity_.z, maxVelocity_.z);
				// 色
				emitParamater_.color.x = Random::GenerateFloat(minColor_.x, maxColor_.x);
				emitParamater_.color.y = Random::GenerateFloat(minColor_.y, maxColor_.y);
				emitParamater_.color.z = Random::GenerateFloat(minColor_.z, maxColor_.z);

				// 生存時間
				emitParamater_.lifeTime = Random::GenerateFloat(minLifeTime_, maxLifeTime_);

				particle_->AddNewParticle(emitParamater_);
			}
			break;
			// X軸方向に放射状に発生
		case kRadialX:
			// 発生個数分ループ
			for (uint32_t i = 0; i < count_; i++) {
				// サイズ
				float size = Random::GenerateFloat(minSize_, maxSize_);
				emitParamater_.scale.x = size;
				emitParamater_.scale.y = size;
				emitParamater_.scale.z = size;
				// 移動量
				float angle = 2.0f * std::numbers::pi_v<float> *i / count_;
				emitParamater_.velocity.x = 0.0f;
				emitParamater_.velocity.y = speed_ * std::sin(angle);
				emitParamater_.velocity.z = speed_ * std::cos(angle);

				// 色
				emitParamater_.color.x = Random::GenerateFloat(minColor_.x, maxColor_.x);
				emitParamater_.color.y = Random::GenerateFloat(minColor_.y, maxColor_.y);
				emitParamater_.color.z = Random::GenerateFloat(minColor_.z, maxColor_.z);

				// 生存時間
				emitParamater_.lifeTime = Random::GenerateFloat(minLifeTime_, maxLifeTime_);

				particle_->AddNewParticle(emitParamater_);
			}
			break;
			// Y軸方向に放射状に発生
		case kRadialY:
			// 発生個数分ループ
			for (uint32_t i = 0; i < count_; i++) {
				// サイズ
				float size = Random::GenerateFloat(minSize_, maxSize_);
				emitParamater_.scale.x = size;
				emitParamater_.scale.y = size;
				emitParamater_.scale.z = size;

				// 移動量
				float angle = 2.0f * std::numbers::pi_v<float> *i / count_;
				emitParamater_.velocity.x = speed_ * std::cos(angle);
				emitParamater_.velocity.y = 0.0f;
				emitParamater_.velocity.z = speed_ * std::sin(angle);

				// 色
				emitParamater_.color.x = Random::GenerateFloat(minColor_.x, maxColor_.x);
				emitParamater_.color.y = Random::GenerateFloat(minColor_.y, maxColor_.y);
				emitParamater_.color.z = Random::GenerateFloat(minColor_.z, maxColor_.z);

				// 生存時間
				emitParamater_.lifeTime = Random::GenerateFloat(minLifeTime_, maxLifeTime_);

				particle_->AddNewParticle(emitParamater_);
			}
			break;
			// Z軸方向に放射状に発生
		case kRadialZ:
			// 発生個数分ループ
			for (uint32_t i = 0; i < count_; i++) {
				// サイズ
				float size = Random::GenerateFloat(minSize_, maxSize_);
				emitParamater_.scale.x = size;
				emitParamater_.scale.y = size;
				emitParamater_.scale.z = size;

				// 移動量
				float angle = 2.0f * std::numbers::pi_v<float> *i / count_;
				emitParamater_.velocity.x = speed_ * std::cos(angle);
				emitParamater_.velocity.y = speed_ * std::sin(angle);
				emitParamater_.velocity.z = 0.0f;

				// 色
				emitParamater_.color.x = Random::GenerateFloat(minColor_.x, maxColor_.x);
				emitParamater_.color.y = Random::GenerateFloat(minColor_.y, maxColor_.y);
				emitParamater_.color.z = Random::GenerateFloat(minColor_.z, maxColor_.z);

				// 生存時間
				emitParamater_.lifeTime = Random::GenerateFloat(minLifeTime_, maxLifeTime_);

				particle_->AddNewParticle(emitParamater_);
			}
			break;
	}
}

void Emitter::SetParticle(const std::string& particleName) {
	// パーティクルがなければassert
	particle_ = SUGER::FindParticle(particleName);
}

void Emitter::SetCount(const uint32_t& count) {
	count_ = count;
}

void Emitter::SetFrequency(const float& frequency) {
	frequency_ = frequency;
}

void Emitter::SetIsRepeat(const bool& isRepeat) {
	isRepeat_ = isRepeat;
}

void Emitter::SetEmitType(const EmitType& emitType) {
	emitType_ = emitType;
}

void Emitter::SetBlendMode(const BlendMode& blendMode) {
	blendMode_ = blendMode;
}

void Emitter::SetMinSize(float minSize) {
	minSize_ = minSize;
}

void Emitter::SetMaxSize(float maxSize) {
	maxSize_ = maxSize;
}

void Emitter::SetMinPosition(const Vector3& minPosition) {
	minTranslate_ = minPosition;
}

void Emitter::SetMaxPosition(const Vector3& maxPosition) {
	maxTranslate_ = maxPosition;
}

void Emitter::SetMinVelocity(const Vector3& minVelocity) {
	minVelocity_ = minVelocity;
}

void Emitter::SetMaxVelocity(const Vector3& maxVelocity) {
	maxVelocity_ = maxVelocity;
}

void Emitter::SetMinColor(const Vector3& minColor) {
	minColor_ = minColor;
}

void Emitter::SetMaxColor(const Vector3& maxColor) {
	maxColor_ = maxColor;
}

void Emitter::SetMinLifeTime(float minLifeTime) {
	minLifeTime_ = minLifeTime;
}

void Emitter::SetMaxLifeTime(float maxLifeTime) {
	maxLifeTime_ = maxLifeTime;
}