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

	// 弾リストをコライダーリストにセット
	void SetColliderListBullet();

	// レールカメラのトランスフォームセット
	void SetRailTransform(WorldTransform* railTransform);

	const float& GetRotateX();

	void SetT(const float& t) {
		t_ = t;
	}

	void PlusScore() {
		scorePoint_ += 50;
	}

private:
	// プレイヤーオブジェクトのコントローラ
	Object3DController player_;
	// レティクルのコントローラ
	Object2DController reticle_;
	// スコア表示のコントローラ
	Object2DController score_;
	// レティクルのスクリーン座標
	Vector2 reticlePosition_{};
	// レティクルのワールド座標
	WorldTransform reticleTransform_{};
	// カメラから照準への距離
	const float kDistanceReticle_ = 10.0f;
	// 弾のリスト
	std::list<PlayerBullet*> bullets_;
	// 弾の速度
	const float kBulletSpeed_ = 1.5f;
	// 弾を発射する位置のオフセット
	const Vector3 kBulletShotOffset_ = { 0.0f,-0.5f,-0.0f };

	float t_ = 0.0f;


	uint32_t scorePoint_ = 0;

};