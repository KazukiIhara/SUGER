#include "Object3dController.h"

#include <cassert>

#include "3d/object/Object3d.h"

void Object3DController::Initialize(Object3D* object3d) {
	// nullptrだった場合assert
	assert(object3d);
	// オブジェクトをセット
	SetObject3D(object3d);
}

void Object3DController::SetScale(const Vector3& scale) {
	object3d_->SetTranslate(scale);
}

void Object3DController::SetRotate(const Vector3& rotate) {
	object3d_->SetTranslate(rotate);
}

void Object3DController::SetTranslate(const Vector3& translate) {
	object3d_->SetTranslate(translate);
}

void Object3DController::SetModel(const std::string& filePath) {
	object3d_->SetModel(filePath);
}

void Object3DController::SetObject3D(Object3D* object3d) {
	object3d_ = object3d;
}
