#include "Object3dController.h"

#include <cassert>

#include "3d/object/Object3d.h"

void Object3DController::Initialize(Object3D* object3d) {
	// nullptrだった場合assert
	assert(object3d);
	// オブジェクトをセット
	SetObject(object3d);
}

void Object3DController::SetScale(const Vector3& scale) {
	object3d_->SetScale(scale);
}

void Object3DController::SetRotate(const Vector3& rotate) {
	object3d_->SetRotate(rotate);
}

void Object3DController::SetTranslate(const Vector3& translate) {
	object3d_->SetTranslate(translate);
}

void Object3DController::SetIsDelete(const bool& isDelete) {
	object3d_->SetIsDelete(isDelete);
}

void Object3DController::SetParent(WorldTransform* parent) {
	object3d_->SetParent(parent);
}

void Object3DController::SetModel(const std::string& filePath) {
	object3d_->SetModel(filePath);
}

void Object3DController::SetIsActive(const bool& isActive) {
	object3d_->SetIsActive(isActive);
}

void Object3DController::SetEnableLightning(const bool& enableLightning) {
	object3d_->SetEnableLightning(enableLightning);
}

const Vector3& Object3DController::GetScale() {
	return object3d_->GetScale();
}

const Vector3& Object3DController::GetRotate() {
	return object3d_->GetRotate();
}

const Vector3& Object3DController::GetTranslate() {
	return object3d_->GetTranslate();
}

bool Object3DController::GetIsDelete() {
	return object3d_->GetIsDelete();
}

WorldTransform* Object3DController::GetWorldTransform() {
	return object3d_->GetWorldTransform();
}

Camera* Object3DController::GetCamera() {
	return object3d_->GetCamera();
}

void Object3DController::SetObject(Object3D* object3d) {
	object3d_ = object3d;
}
