#pragma once

#include <list>

#include "3d/controller/Object3dController.h"
#include "2d/controller/Object2dController.h"
#include "worldTransform/WorldTransform.h"
#include "objects/playerBullet/PlayerBullet.h"

class Player {
public:
	Player() = default;
	~Player() = default;

	// 初期化
	void Initialize();
	// 更新
	void Update();

	// 照準の操作
	void MoveReticle();

	// 照準の座標変換
	void ScreenToWorld();

	// 攻撃
	void Attack();

	// レールカメラのトランスフォームセット
	void SetRailTransform(WorldTransform* railTransform);

private:
	// プレイヤーオブジェクトのコントローラ
	Object3DController player_;
	// レティクルのコントローラ
	Object2DController reticle_;
	// レティクルのスクリーン座標
	Vector2 reticlePosition_{};
	// レティクルのワールド座標
	WorldTransform reticleTransform_{};
	// カメラから照準への距離
	const float kDistanceReticle_ = 200.0f;
	// 弾のリスト
	std::list<PlayerBullet*> bullets_;
	// 弾の速度
	const float kBulletSpeed_ = 1.5f;
};