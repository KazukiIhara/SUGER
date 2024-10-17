// This
#include "SampleScene.h"

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "framework/SUGER.h"
#include "debugTools/logger/Logger.h"


void SampleScene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();

	// 
	// シーンの初期化処理ここから
	// 


	// トランスフォームの初期化
	teapotTransform_.Initialize();
	// オブジェクトの生成と、モデルの読み込み
	SUGER::Create3DObject(teapotTransform_, "teapot", "teapot");
	SUGER::Create2DObject("nero", "nero.jpg");
	SUGER::CreateParticle(teapotTransform_, "normal", "mashu.jpg");
}

void SampleScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void SampleScene::Update() {

	// 
	// シーンの更新処理ここから
	// 



	// 
	// シーンの更新処理ここまで
	//

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}
