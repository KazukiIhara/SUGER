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
	SUGER::CreatePlaneParticle("plane", "circle.png");

	// オブジェクト3Dコントローラの初期化
	teapot_.Initialize(SUGER::FindObject3D("teapot"));
	// オブジェクト2Dコントローラの初期化
	jeanne_.Initialize(SUGER::FindObject2D("jeanne"));
	// パーティクルコントローラの初期化
	plane_.Initialize(SUGER::FindParticle("plane"));

	// オブジェクト3Dコントローラを使ってトランスレートをセット
	teapot_.SetTranslate(Vector3(1.0f, 0.0f, 0.0f));

	// オブジェクト2Dコントローラを使ってポジションとアンカーポイントをセット
	jeanne_.SetPosition(jeanne_.GetSize() / 2.0f);
	jeanne_.SetAnchorPoint(Vector2(0.5f, 0.5f));

	// teapotを非アクティブ化
	teapot_.SetIsActive(false);

	// jeanneを非アクティブ化
	jeanne_.SetIsActive(false);

	// パーティクルを非アクティブ化
	plane_.SetIsActive(false);
	 
}

void SampleScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void SampleScene::Update() {

	// 
	// シーンの更新処理ここから
	// 

	// スプライトを回転
	jeanne_.SetRotation(jeanne_.GetRotation() + 0.01f);


	// 
	// シーンの更新処理ここまで
	//

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}
