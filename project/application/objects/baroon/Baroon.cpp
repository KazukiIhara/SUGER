#include "Baroon.h"

#include "framework/SUGER.h"

void Baroon::Initialize(const std::string& name, const std::string& filePath, const EulerTransform3D& transform) {
	// 引数からオブジェクトを生成。コントローラを初期化。
	controller_.Initialize(SUGER::FindObject3D(SUGER::Create3DObject(name, filePath, transform)));
	// コライダーのサイズを変更
	SetRadius(0.5f);

}

void Baroon::Update() {

}

void Baroon::OnCollision(Collider* other) {
	// 衝突相手のカテゴリを取得
	ColliderCategory category = other->GetCategory();

	switch (category) {
		case kPlayerBullet:
			isDelete_ = true;
			controller_.SetIsDelete(true);
			break;
		default:
			break;
	}
}
