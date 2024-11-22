#include "Emitter.h"

#include "framework/SUGER.h"
#include "random/Random.h"

void Emitter::Initialize() {
	// 基底クラスの初期化
	Empty::Initialize();

	// 発生設定の初期化
	// 発生数は1
	count_ = 1;
	// 移動量は0
	emitSetting_.velocity = { 0.0f,0.0f,0.0f };
	// 色は白
	emitSetting_.color = { 1.0f,1.0f,1.0f,1.0f };
	// 生存時間をひとまず5秒に設定
	emitSetting_.lifeTime = 5.0f;
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
	emitSetting_.position = GetWorldPosition();
	// 発生個数分ループ
	for (uint32_t i = 0; i < count_; i++) {
		// ランダム発生処理
		if (isRandom_) {
			// 発生座標
			emitSetting_.position.x = Random::GenerateFloat(randomMinTranslate_.x, randomMaxTranslate_.x);
			emitSetting_.position.y = Random::GenerateFloat(randomMinTranslate_.y, randomMaxTranslate_.y);
			emitSetting_.position.z = Random::GenerateFloat(randomMinTranslate_.z, randomMaxTranslate_.z);
			// 移動量
			emitSetting_.velocity.x = Random::GenerateFloat(randomMinVelocity_.x, randomMaxVelocity_.x);
			emitSetting_.velocity.y = Random::GenerateFloat(randomMinVelocity_.y, randomMaxVelocity_.y);
			emitSetting_.velocity.z = Random::GenerateFloat(randomMinVelocity_.z, randomMaxVelocity_.z);
			// 色
			emitSetting_.color.x = Random::GenerateFloat(randomMinColor_.x, randomMaxColor_.x);
			emitSetting_.color.y = Random::GenerateFloat(randomMinColor_.y, randomMaxColor_.y);
			emitSetting_.color.z = Random::GenerateFloat(randomMinColor_.z, randomMaxColor_.z);
			// 生存時間
			emitSetting_.lifeTime = Random::GenerateFloat(randomMinLifeTime_, randomMaxLifeTime_);
		}

		//
		// このクラスを継承して、ここにemitSettingを変更する処理を追加することで、様々なパーティクルを出すことが可能
		//

		particle_->AddNewParticle(emitSetting_);
	}
}

void Emitter::SetParticle(const std::string& particleName) {
	// パーティクルがなければassert
	particle_ = SUGER::FindFixParticle(particleName);
}

void Emitter::SetCount(const uint32_t& count) {
	count_ = count;
}

void Emitter::SerFrequency(const float& frequency) {
	frequency_ = frequency;
}

void Emitter::SetIsRepeat(const bool& isRepeat) {
	isRepeat_ = isRepeat;
}

void Emitter::SetIsRandom(const bool& isRandom) {
	isRandom_ = isRandom;
}

void Emitter::SetRandomMinPosition(const Vector3& randomMinPosition) {
	randomMinTranslate_ = randomMinPosition;
}

void Emitter::SetRandomMaxPosition(const Vector3& randomMaxPosition) {
	randomMaxTranslate_ = randomMaxPosition;
}

void Emitter::SetRandomMinVelocity(const Vector3& randomMinVelocity) {
	randomMinVelocity_ = randomMinVelocity;
}

void Emitter::SetRandomMaxVelocity(const Vector3& randomMaxVelocity) {
	randomMaxVelocity_ = randomMaxVelocity;
}

void Emitter::SetRandomMinColor(const Vector3& randomMinColor) {
	randomMinColor_ = randomMinColor;
}

void Emitter::SetRandomMaxColor(const Vector3& randomMaxColor) {
	randomMaxColor_ = randomMaxColor;
}

void Emitter::SetRandomMinLifeTime(float randomMinLifeTime) {
	randomMinLifeTime_ = randomMinLifeTime;
}

void Emitter::SetRandomMaxLifeTime(float randomMaxLifeTime) {
	randomMaxLifeTime_ = randomMaxLifeTime;
}