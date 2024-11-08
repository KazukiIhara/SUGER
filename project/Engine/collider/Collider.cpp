#include "Collider.h"

void Collider::Initialize() {
	worldTransform_.Initialize();
}

void Collider::UpdateWorldTransform() {
	// ワールド座標をワールドトランスフォームに適用
	worldTransform_.translate_ = GetCenterPosition();
	worldTransform_.scale_ = { radius_,radius_,radius_ };
	worldTransform_.Update();
}

void Collider::SetColliderType(ColliderType colliderType) {
	colliderType_ = colliderType;
}

ColliderType Collider::GetColliderType() const {
	return colliderType_;
}

uint32_t Collider::GetTypeID() const {
	return typeID_;
}

void Collider::SetTypeID(uint32_t typeID){ 
	typeID_ = typeID;
}