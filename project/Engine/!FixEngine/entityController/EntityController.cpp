#include "EntityController.h"

#include "framework/SUGER.h"

void EmtityContoroller::Initialize(const std::string& name) {
	// エンティティをマネージャからセット
	entity_ = SUGER::FindEntity(name);
	// なかったらassert
	assert(entity_);
}

void EmtityContoroller::SetScale(const Vector3& scale) {
	entity_->SetScale(scale);
}

void EmtityContoroller::SetRotate(const Vector3& rotate) {
	entity_->SetRotate(rotate);
}

void EmtityContoroller::SetTranslate(const Vector3& translate) {
	entity_->SetTranslate(translate);
}

void EmtityContoroller::SetParent(WorldTransform* parent) {
	entity_->SetParent(parent);
}

void EmtityContoroller::SetColor(const Vector4& color) {
	entity_->SetColor(color);
}

void EmtityContoroller::SetEnableLight(const bool& enbleLight) {
	entity_->SetEnableLight(enbleLight);
}

const Vector3& EmtityContoroller::GetScale() const {
	return entity_->GetScale();
}

const Vector3& EmtityContoroller::GetRotate() const {
	return entity_->GetRotate();
}

const Vector3& EmtityContoroller::GetTranslate() const {
	return entity_->GetTranslate();
}

WorldTransform* EmtityContoroller::GetWorldTransformPtr() {
	return entity_->GetWorldTransformPtr();
}

Camera* EmtityContoroller::GetCameraPtr() {
	return entity_->GetCamera();
}


