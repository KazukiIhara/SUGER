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

