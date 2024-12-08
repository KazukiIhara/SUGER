#pragma once

// Common
#include "iScene/base/BaseScene.h"
#include "2d/controller/Object2dController.h"
#include "3d/entityController/EntityController.h"
#include "VFX/particle/emitterController/EmitterController.h"
#include "3d/lineController/LineController.h"

// CG3Scene
#include "VFX/explosion/Explosion.h"

class CG3Scene:public BaseScene {
public:
	CG3Scene() = default;
	~CG3Scene() = default;

	// 初期化
	void Initialize()override;
	// 終了
	void Finalize()override;

	// プレイフェーズ初期化
	void SceneStatePlayInitialize()override;
	// プレイフェーズ更新
	void SceneStatePlayUpdate()override;

private:
	// Emitterコントローラ
	EmitterController emitter_;
	// Explosion
	Explosion explosion_;
};