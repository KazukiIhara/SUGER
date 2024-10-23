// This
#include "ShootingCoasterScene.h"

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "framework/SUGER.h"
#include "debugTools/logger/Logger.h"


void ShootingCoasterScene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();

	// 
	// シーンの初期化処理ここから
	// 
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize();
	//SUGER::SetSceneCamera(railCamera_.get());

	SUGER::LoadJsonLevelData("level1");

}

void ShootingCoasterScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void ShootingCoasterScene::Update() {

	// 
	// シーンの更新処理ここから
	// 

	//// レールカメラの更新
	//railCamera_->Update();

	// 
	// シーンの更新処理ここまで
	//

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}
