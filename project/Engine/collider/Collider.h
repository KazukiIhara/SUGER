#pragma once

#include <cstdint>

#include "math/function/MathFunction.h"
#include "worldTransform/WorldTransform.h"

class Collider {
public:

	Collider() = default;
	virtual ~Collider() = default;
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
	// 衝突時に呼ばれる関数
	virtual void OnCollision([[maybe_unused]] Collider* other) {
	}
	// 中心座標を取得
	virtual Vector3 GetCenterPosition()const = 0;

	// 種別IDを取得
	uint32_t GetTypeID()const { return typeID_; }
	// 種別IDを指定
	void SetTypeID(uint32_t typeID) { typeID_ = typeID; }

private:
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// 衝突半径
	float radius_ = 1.0f;
	// 種別ID
	uint32_t typeID_ = 0u;

};
