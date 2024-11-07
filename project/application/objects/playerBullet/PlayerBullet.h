#pragma once

#include <cstdint>
#include "3d/controller/Object3dController.h"


class PlayerBullet {
public:
	PlayerBullet() = default;
	~PlayerBullet() = default;

	void Initialize(const Vector3& position, const Vector3& velocity);

	void Update();

	bool GetIsDead();

private:
	// コントローラ
	Object3DController bullet_;
	// 移動量
	Vector3 velocity_{};
	// 寿命
	static const int32_t kLifeTime_ = 60 * 5;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime_;

	bool isDead_ = false;
};
