#include "TitleScene.h"

// MyHedder
#include "framework/SUGER.h"

void TitleScene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();

	// 
	// シーンの初期化処理ここから
	// 

	SUGER::Create2DObject("PushA", "pushA.png");

	pushA_.Initialize(SUGER::FindObject2D("PushA"));
	pushA_.SetAnchorPoint(Vector2(0.5f, 0.5f));
	pushA_.SetPosition(Vector2(WindowManager::kClientWidth / 2.0f, 800.0f));
}

void TitleScene::Finalize() {}

void TitleScene::Update() {

	if (SUGER::TriggerButton(0, ButtonA)) {
		ChangeScene("SHOOTINGCOASTER");
	}

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}
