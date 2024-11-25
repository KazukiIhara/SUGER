#pragma once

#include "math/function/MathFunction.h"
#include "enum/ColliderEnum.h"

class Collider {
public:
	Collider() = default;
	~Collider() = default;

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();

	// ワールド座標のセッター
	void SetWorldPosition(const Vector3& worldPosition);

	// コライダータイプのセッター
	void SetColliderType(const ColliderType& colliderType);

	// サイズのセット
	void SetSize(const float& size);

	// ワールド座標のゲッター
	Vector3 GetWorldPosition()const;

	// コライダータイプのゲッター
	ColliderType GetColliderType()const;

	// サイズの取得
	float GetSize()const;

private:
	// ワールド座標
	Vector3 worldPosition_{};
	// サイズ
	float size_ = 1.0f;
	// コライダータイプ
	ColliderType colliderType_ = kSphere;
};