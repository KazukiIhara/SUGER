#pragma once
#include "3d/empty/empty.h"
#include "!FixEngine/particle/Particle.h"

class Emitter:public Empty {
public:
	Emitter() = default;
	~Emitter() = default;

	// 更新
	void Update()override;

	// パーティクル発生
	virtual void Emit();

	// パーティクルのセット
	void SetParticle(const std::string& particleName);

	// 発生数のセット
	void SetCount(const uint32_t& count);
	// 発生頻度のセット
	void SerFrequency(const float& frequency);
	// 繰り返し発生フラグのセット
	void SetIsRepeat(const bool& isRepeat);

protected:
	// 発生数
	uint32_t count_ = 1;
	// 発生頻度
	float frequency_ = 0.5f;
	// 繰り返し発生させるかどうか
	bool isRepeat_ = false;
	// 頻度用時刻
	float frequencyTime_ = 0.0f;

	// セットするパーティクル
	Particle* particle_ = nullptr;
};
