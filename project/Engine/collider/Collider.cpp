#include "Collider.h"

void Collider::Initialize() {
	worldTransform_.Initialize();
}

void Collider::UpdateWorldTransform(const WorldTransform& transform, const Vector3& colliderOffset) {
	// ワールド座標をワールドトランスフォームに適用
	worldTransform_.translate_ = Transform(colliderOffset, transform.worldMatrix_);
	worldTransform_.scale_ = { radius_,radius_,radius_ };
	worldTransform_.Update();
}

void Collider::SetRadius(const float& radius) {
	radius_ = radius;
}

void Collider::SetType(ColliderType colliderType) {
	colliderType_ = colliderType;
}

void Collider::SetCategory(ColliderCategory category) {
	category_ = category;
}

void Collider::SetSerialNumber(const uint32_t& serialNumber) {
	serialNumber_ = serialNumber;
}

float Collider::GetRadius()const {
	return radius_;
}

ColliderType Collider::GetType() const {
	return colliderType_;
}

ColliderCategory Collider::GetCategory() const {
	return category_;
}

uint32_t Collider::GetSerialNumber() const {
	return serialNumber_;
}
