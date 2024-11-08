#include "Collider.h"

void Collider::Initialize() {
	worldTransform_.Initialize();
}

void Collider::UpdateWorldTransform(const WorldTransform &transform, const Vector3 &colliderOffset) {
	// ワールド座標をワールドトランスフォームに適用
	worldTransform_.translate_ = Transform(colliderOffset, transform.worldMatrix_);
	worldTransform_.scale_ = { radius_,radius_,radius_ };
	worldTransform_.Update();
}

void Collider::SetType(ColliderType colliderType) {
	colliderType_ = colliderType;
}

void Collider::SetCategory(ColliderCategory category) {
	category_ = category;
}

ColliderType Collider::GetType() const {
	return colliderType_;
}

ColliderCategory Collider::GetCategory() const {
	return category_;
}