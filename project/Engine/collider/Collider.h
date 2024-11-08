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
	void UpdateWorldTransform(const WorldTransform& transform, const Vector3& colliderOffset = { 0.0f,0.0f,0.0f });

	// 半径を設定
	void SetRadius(const float& radius) {
		radius_ = radius;
	}

	// コライダーのタイプを設定
	void SetType(ColliderType colliderType);

	// 種別IDを指定
	void SetCategory(ColliderCategory category);


	// 半径を取得
	float GetRadius() {
		return radius_;
	}

	// コライダータイプの取得
	ColliderType GetType()const;

	// 種別IDを取得
	ColliderCategory GetCategory()const;


private:
	// ワールドトランスフォーム
	WorldTransform worldTransform_;
	// 衝突半径
	float radius_ = 1.0f;
	// コライダーのタイプ
	ColliderType colliderType_ = kSphere;
	// 種別ID
	ColliderCategory category_ = A;

};
