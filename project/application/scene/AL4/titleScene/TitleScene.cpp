#include "TitleScene.h"

// MyHedder
#include "framework/SUGER.h"

void TitleScene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();

	// 
	// シーンの初期化処理ここから
	// 

}

void TitleScene::Finalize() {}

void TitleScene::Update() {

	if (SUGER::TriggerButton(0, ButtonA)) {
		ChangeScene("SHOOTINGCOASTER");
	}

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}
