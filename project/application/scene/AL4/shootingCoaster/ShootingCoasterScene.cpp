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
	SUGER::SetSceneCamera(railCamera_.get());

	// レールの生成処理
	for (uint32_t i = 0; i < kRailNum_; i++) {
		// レールのトランスフォームを初期化
		railTransform_[i].translate.z = static_cast<float>(i);
		railCamera_->PushBackControlPoint(railTransform_[i].translate);
		// 文字列 "rail" の末尾に i を追加
		std::string railName = "rail" + std::to_string(i);
		// レールの生成
		SUGER::Create3DObject(railName.c_str(), "rail", railTransform_[i]);
	}
	SUGER::SetSceneCamera(debugCamera_.get());
}

void ShootingCoasterScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void ShootingCoasterScene::Update() {

	// 
	// シーンの更新処理ここから
	// 

	// レールカメラの更新
	railCamera_->Update();

	// 
	// シーンの更新処理ここまで
	//

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}
