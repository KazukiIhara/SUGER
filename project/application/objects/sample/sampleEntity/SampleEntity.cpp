#include "SampleEntity.h"

#include "framework/SUGER.h"

void SampleEntity::Initialize() {
	// モデルの読み込みとオブジェクトの作成、コントローラへの登録
	controller_.Initialize(SUGER::FindObject3D(SUGER::Create3DObject("sampleEntity", "teapot")));
}

void SampleEntity::Update() {}

void SampleEntity::OnCollision(Collider* other) {
	// 衝突相手の種別を取得
	ColliderCategory category = other->GetCategory();


	controller_.SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
}

