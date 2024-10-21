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
	
	// カメラの設定
	sceneCamera_ = std::make_unique<Camera>();
	sceneCamera_->Initialize();

	// シーンにカメラをセット
	SUGER::SetSceneCamera(sceneCamera_.get());

	// オブジェクトの生成と、モデルの読み込み
	SUGER::Create3DObject("teapot", "teapot");
	SUGER::Create2DObject("jeanne", "jeanne.jpg");
	SUGER::CreatePlaneParticle("normal", "circle.png");

	// オブジェクト3Dコントローラの初期化
	teapot_.Initialize(SUGER::FindObject3D("teapot"));
}

void SampleScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void SampleScene::Update() {

	// 
	// シーンの更新処理ここから
	// 

	// オブジェクトコントローラを使ってトランスレートをセット
	teapot_.SetTranslate(Vector3(1.0f, 0.0f, 0.0f));

	// 
	// シーンの更新処理ここまで
	//

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}
