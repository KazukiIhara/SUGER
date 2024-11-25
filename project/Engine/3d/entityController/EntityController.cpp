#include "EntityController.h"

#include "framework/SUGER.h"

void EntityController::Initialize(const std::string& name) {
	// エンティティをマネージャからセット
	entity_ = SUGER::FindEntity(name);
	// なかったらassert
	assert(entity_);
}

void EntityController::OnCollision(Collider* other) {
	// 衝突相手のカテゴリーを取得
	ColliderCategory category = other->GetColliderCategory();
	switch (category) {
	case kNone:
		break;
	default:
		break;
	}


}

void EntityController::SetScale(const Vector3& scale) {
	entity_->SetScale(scale);
}

void EntityController::SetScale(const float& scale) {
	entity_->SetScale(Vector3(scale, scale, scale));
}

void EntityController::SetRotate(const Vector3& rotate) {
	entity_->SetRotate(rotate);
}

void EntityController::SetTranslate(const Vector3& translate) {
	entity_->SetTranslate(translate);
}

void EntityController::SetParent(WorldTransform* parent) {
	entity_->SetParent(parent);
}

void EntityController::SetColor(const Vector4& color) {
	entity_->SetColor(color);
}

void EntityController::SetEnableLight(const bool& enbleLight) {
	entity_->SetEnableLight(enbleLight);
}

const Vector3& EntityController::GetScale() const {
	return entity_->GetScale();
}

const Vector3& EntityController::GetRotate() const {
	return entity_->GetRotate();
}

const Vector3& EntityController::GetTranslate() const {
	return entity_->GetTranslate();
}

WorldTransform* EntityController::GetWorldTransformPtr() {
	return entity_->GetWorldTransformPtr();
}

Camera* EntityController::GetCameraPtr() {
	return entity_->GetCamera();
}

Collider EntityController::GetCollider() const {
	return entity_->GetCollider();
}


