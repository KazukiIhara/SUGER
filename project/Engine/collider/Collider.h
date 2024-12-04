#pragma once

#include "math/function/MathFunction.h"
#include "enum/ColliderEnum.h"
#include "colliderCategory/ColliderCategory.h"
#include "3d/empty/empty.h"
#include "3d/lineController/LineController.h"

class Collider :public Empty {
public:
	Collider() = default;
	~Collider() = default;

	// 初期化
	void Initialize(const Vector3& worldPosition, const ColliderCategory& colliderCategory, const ColliderType& colliderType, const float& size);
	// 更新
	void Update(const Vector3& worldPosition);
	// 描画
	void Draw();

	// スフィアの描画
	void DrawSphere(const Vector3& center, float radius, uint32_t segments);

	// ワールド座標のセッター
	void SetWorldPosition(const Vector3& worldPosition);

	// コライダータイプのセッター
	void SetColliderType(const ColliderType& colliderType);

	// コライダーカテゴリのセッター
	void SetColliderCategory(const ColliderCategory& colliderCategory);

	// サイズのセット
	void SetSize(const float& size);

	// ワールド座標のゲッター
	Vector3 GetWorldPosition()const;

	// コライダータイプのゲッター
	ColliderType GetColliderType()const;

	// コライダーカテゴリーのゲッター
	ColliderCategory GetColliderCategory()const;

	// サイズの取得
	float GetSize()const;
private:
	// ラインコントローラのセット
	void SetLineController(LineController* lineController);

private:
	// ワールド座標
	Vector3 worldPosition_{};
	// サイズ
	float size_ = 1.0f;
	// コライダータイプ
	ColliderType colliderType_ = ColliderType::kSphere;
	// コライダーカテゴリ
	ColliderCategory colliderCategory_ = ColliderCategory::kNone;
	// ライン描画コントローラ
	LineController* line_;
};