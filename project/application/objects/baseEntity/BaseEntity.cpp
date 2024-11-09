#include "BaseEntity.h"

void BaseEntity::Initialize() {
}

void BaseEntity::Update() {}

Vector3 BaseEntity::GetCenterPosition() {
	// デフォルトではコントローラ経由でオブジェクトの座標を返す
	return ExtractionWorldPos(controller_.GetWorldTransformPtr()->worldMatrix_);
}
