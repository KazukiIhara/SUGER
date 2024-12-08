#pragma once
#include "3d/empty/empty.h"
#include "VFX/particle/emitterController/EmitterController.h"

class Explosion :public Empty {
public:
	Explosion() = default;
	~Explosion() = default;

	// 初期化
	void Initialize()override;
	// 更新
	void Update()override;

	// 発生
	void Emit();

private:
	// デルタタイム
	const float kDeltaTime_ = 1.0f / 60.0f;

	// エミッターコントローラ
	EmitterController sparkEmitter_;
	EmitterController flashEmitter_;
	EmitterController fireEmitter_;
	EmitterController smokeEmitter_;

};