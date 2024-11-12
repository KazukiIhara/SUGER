#pragma once

#include <cstdint>
#include "3d/controller/Object3dController.h"
#include "objects/baseEntity/BaseEntity.h"

class Player;

class PlayerBullet :public BaseEntity {
public:
	PlayerBullet() = default;
	~PlayerBullet() = default;

	void Initialize(const Vector3& position, const Vector3& velocity, Player* player);

	void Update();

	bool GetIsDead();

	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision([[maybe_unused]] Collider* other)override;

private:
	// 移動量
	Vector3 velocity_{};
	// 寿命
	static const int32_t kLifeTime_ = 10;
	// デスタイマー
	int32_t deathTimer_ = kLifeTime_;

	bool isDead_ = false;

	Player* player_;
};
