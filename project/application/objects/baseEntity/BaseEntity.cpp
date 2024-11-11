#include "BaseEntity.h"

Vector3 BaseEntity::GetCenterPosition() {
	// デフォルトではコントローラ経由でオブジェクトの座標を返す
	return ExtractionWorldPos(controller_.GetWorldTransformPtr()->worldMatrix_);
}

void BaseEntity::ClearContactRecord() {
	contactRecord_.Clear();
}
