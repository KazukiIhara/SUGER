#pragma once
#include "3d/empty/empty.h"
#include "!FixEngine/particle/Particle.h"

class Emitter:public Empty {
public:
	Emitter() = default;
	~Emitter() = default;

	// パーティクル発生
	void Emit();

	// パーティクルのセット
	void SetParticle(Particle* particle);

private:
	// パーティクルのデータ
	ParticleData particleData_{};

	// 発生数
	uint32_t count = 5;
	// 発生頻度
	float frequency = 0.5f;
	// 頻度用時刻
	float frequencyTime = 0.0f;
	// 繰り返し発生させるかどうか
	bool isRepeat = false;

	// セットするパーティクル
	Particle* particle_;
};
