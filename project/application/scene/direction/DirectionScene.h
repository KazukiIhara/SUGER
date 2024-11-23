#pragma once

// MyHedder
#include "iScene/base/BaseScene.h"
#include "2d/controller/Object2dController.h"
#include "3d/entityController/EntityController.h"

#include "particle/emitterController/EmitterController.h"

class DirectionScene: public BaseScene {
public:
	DirectionScene() = default;
	~DirectionScene() = default;
	// 初期化
	void Initialize()override;
	// 終了
	void Finalize()override;

	// プレイフェーズ初期化
	void SceneStatusPlayInitialize()override;
	// プレイフェーズ更新
	void SceneStatusPlayUpdate()override;

private:

};