#include "SampleEntity1.h"

#include "framework/SUGER.h"

void SampleEntity1::Initialize() {
	// モデルの読み込みとオブジェクトの作成、コントローラへの登録
	controller_.Initialize(SUGER::FindObject3D(SUGER::Create3DObject("sampleEntity", "teapot")));
	// 初期位置を移動
	controller_.SetTranslate(Vector3(0.0f, 0.0f, 0.0f));

	// シリアルナンバーのセット
	SetSerialNumber(0x00000001);
}

void SampleEntity1::Update() {}

void SampleEntity1::OnCollision(Collider* other) {}
