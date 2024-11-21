#include "Emitter.h"

#include "framework/SUGER.h"
#include "random/Random.h"

void Emitter::Update() {
	// 基底クラスの更新
	Empty::Update();

	// 繰り返しフラグがオンなら繰り返し発生
	if (isRepeat_) {

	}
}

void Emitter::Emit() {
	// パーティクル発生設定
	EmitSetting emitSetting{};
	// 生存時間をひとまず5秒に設定
	emitSetting.lifeTime = 5.0f;
	// 発生個数分ループ
	for (uint32_t i = 0; i < count_; i++) {
		// 移動量は0
		emitSetting.velocity = Random::GenerateVector3(-1.0f, 1.0f);
		// 色は白
		emitSetting.color = Random::GenerateVector4(0.0f, 1.0f);
		emitSetting.color.w = 1.0f;
		particle_->AddNewParticle(GetWorldPosition() + Random::GenerateVector3(-1.0f, 1.0f), emitSetting);
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
