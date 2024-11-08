#pragma once

#include <cstdint>

#include "enum/ColliderEnum.h"

#include "math/function/MathFunction.h"
#include "worldTransform/WorldTransform.h"

class Collider {
public:

	Collider() = default;
	~Collider() = default;
	// 初期化
	void Initialize();

	// ワールドトランスフォームの更新
	void UpdateWorldTransform();

	// 半径を取得
	float GetRadius() {
		return radius_;
	}
	// 半径を設定
	void SetRadius(const float& radius) {
		radius_ = radius;
	}

	// コライダーのタイプを設定
	void SetColliderType(ColliderType colliderType);

	// コライダータイプの取得
	ColliderType GetColliderType()const;

	// 種別IDを取得
	uint32_t GetTypeID()const;
	// 種別IDを指定
	void SetTypeID(uint32_t typeID);

private:
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// 衝突半径
	float radius_ = 1.0f;
	// コライダーのタイプ
	ColliderType colliderType_ = kSphere;
	// 種別ID
	uint32_t typeID_ = 0u;

};
