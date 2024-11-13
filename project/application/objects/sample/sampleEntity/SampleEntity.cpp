#include "SampleEntity.h"

#include "framework/SUGER.h"

void SampleEntity::Initialize() {
	// モデルの読み込みとオブジェクトの作成、コントローラへの登録
	controller_.Initialize(SUGER::FindObject3D(SUGER::Create3DObject("sampleEntity", "boxMan")));
	// 初期位置を移動
	controller_.SetTranslate(Vector3(0.0f, 0.0f, 0.0f));

}

void SampleEntity::Update() {
	if (SUGER::PushKey(DIK_A)) {
		controller_.SetTranslate(controller_.GetTranslate() - Vector3(0.1f, 0.0f, 0.0f));
	} else if (SUGER::PushKey(DIK_D)) {
		controller_.SetTranslate(controller_.GetTranslate() + Vector3(0.1f, 0.0f, 0.0f));
	}
}

void SampleEntity::OnCollision(Collider* other) {
	// 一度衝突したColliderとは、衝突記録をクリアするまで衝突しないようにもできる
	uint32_t serialNumber = other->GetSerialNumber();

	if (contactRecord_.CheckRecord(serialNumber)) {
		return;
	}

	// 衝突記録に追加
	contactRecord_.AddRecord(serialNumber);

	// 衝突相手のカテゴリを取得
	ColliderCategory category = other->GetCategory();

	// カテゴリごとのリアクションを行う
	if (category == kNone) {

		// 衝突している間色を変更
		controller_.SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

