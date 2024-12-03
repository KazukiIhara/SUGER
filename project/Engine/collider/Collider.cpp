#include "Collider.h"

void Collider::Initialize(const Vector3& worldPosition, const ColliderCategory& colliderCategory, const ColliderType& colliderType, const float& size) {
	// ワールド座標をセット
	SetWorldPosition(worldPosition);
	// コライダーカテゴリーをセット
	SetColliderCategory(colliderCategory);
	// コライダータイプをセット
	SetColliderType(colliderType);
	// コライダーのサイズをセット
	SetSize(size);
}

void Collider::Update(const Vector3& worldPosition) {
	// ワールド座標をセット
	SetWorldPosition(worldPosition);
}

void Collider::Draw() {

}

void Collider::SetWorldPosition(const Vector3& worldPosition) {
	worldPosition_ = worldPosition;
}

void Collider::SetColliderType(const ColliderType& colliderType) {
	colliderType_ = colliderType;
}

void Collider::SetColliderCategory(const ColliderCategory& colliderCategory) {
	colliderCategory_ = colliderCategory;
}

void Collider::SetSize(const float& size) {
	size_ = size;
}

Vector3 Collider::GetWorldPosition() const {
	return worldPosition_;
}

ColliderType Collider::GetColliderType() const {
	return colliderType_;
}

ColliderCategory Collider::GetColliderCategory() const {
	return colliderCategory_;
}

float Collider::GetSize() const {
	return size_;
}
