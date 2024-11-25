#include "Collider.h"

void Collider::Initialize() {

}

void Collider::Update() {

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
