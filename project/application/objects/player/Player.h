#pragma once

#include "3d/controller/Object3dController.h"
#include "2d/controller/Object2dController.h"

class Player {
public:
	Player() = default;
	~Player() = default;

	// 初期化
	void Initialize();
	// 更新
	void Update();

	// レールカメラのトランスフォームセット
	void SetRailTransform(WorldTransform* railTransform);

private:
	// プレイヤーオブジェクトのコントローラ
	Object3DController player_;
	// レティクルのコントローラ
	Object2DController reticle_;
};