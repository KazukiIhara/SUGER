#include "Baroon.h"

#include "framework/SUGER.h"

void Baroon::Initialize(const std::string& name, const std::string& filePath, const EulerTransform3D& transform) {
	controller_.Initialize(SUGER::FindObject3D(SUGER::Create3DObject(name, filePath, transform)));
}

void Baroon::Update() {

}

void Baroon::OnCollision(Collider* other) {
	// 衝突相手のカテゴリを取得
	ColliderCategory category = other->GetCategory();

	switch (category) {
		case kPlayerBullet:
			controller_.SetIsDelete(true);
			break;
		default:
			break;
	}
}
