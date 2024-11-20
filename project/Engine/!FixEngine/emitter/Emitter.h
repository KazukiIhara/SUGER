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
	void Emit();

	// パーティクルのセット
	void SetParticle(const std::string& particleName);

private:
	// 発生数
	uint32_t count_ = 5;
	// 発生頻度
	float frequency_ = 0.5f;
	// 頻度用時刻
	float frequencyTime_ = 0.0f;
	// 繰り返し発生させるかどうか
	bool isRepeat_ = false;

	// セットするパーティクル
	Particle* particle_ = nullptr;
};
