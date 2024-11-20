#pragma once
#include "3d/empty/empty.h"
#include "!FixEngine/particle/Particle.h"

class Emitter :public Empty {
public:
	Emitter() = default;
	~Emitter() = default;

	// 初期化
	void Initialize(Particle* particle);

	// パーティクル発生
	void Emit();

private:
	// パーティクルのセット
	void SetParticle(Particle* particle);

private:
	// セットするパーティクル
	Particle* particle_;

	// 発生数
	uint32_t count;
	// 発生頻度
	float frequency;
	// 頻度用時刻
	float frequencyTime;
	// 繰り返し発生させるかどうか
	bool isRepeat;
};
