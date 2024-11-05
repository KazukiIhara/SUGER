#pragma once

#include "3d/controller/Object3dController.h"

class Player {
public:
	Player() = default;
	~Player() = default;

	// 初期化
	void Initialize();
	// 更新
	void Update();

private:
	// プレイヤーオブジェクトのコントローラ
	Object3DController player_;

};