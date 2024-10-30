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
	//SUGER::SetSceneCamera(sceneCamera_.get());

	// オブジェクトの生成と、モデルの読み込み
	SUGER::Create3DObject("sample", "teapot");
	SUGER::Create3DObject("skinningSample", "PronamaChan");
	SUGER::Create2DObject("pronama_chan", "pronama_chan.png");
	SUGER::CreatePlaneParticle("plane", "circle.png");

	// オブジェクト3Dコントローラの初期化
	sample_.Initialize(SUGER::FindObject3D("sample"));
	// スキニング用オブジェクト3Dコントローラの初期化
	skinningSample_.Initialize(SUGER::FindObject3D("skinningSample"));
	// オブジェクト2Dコントローラの初期化
	pronama_chan.Initialize(SUGER::FindObject2D("pronama_chan"));
	// パーティクルコントローラの初期化
	plane_.Initialize(SUGER::FindParticle("plane"));

	// humanをちょっと右にずらす
	skinningSample_.SetTranslate(Vector3(1.0f, 0.0f, 0.0f));
	// humanを少しこっちに向ける
	skinningSample_.SetRotate(Vector3(0.0f, 3.14f, 0.0f));

	// teapotをちょっと左にずらす
	sample_.SetTranslate(Vector3(-1.0f, 0.0f, 0.0f));

	// オブジェクト2Dコントローラを使ってポジションとアンカーポイントをセット
	pronama_chan.SetSize(Vector2(400.0f, 400.0f));
	pronama_chan.SetPosition(pronama_chan.GetSize() / 2.0f);
	pronama_chan.SetAnchorPoint(Vector2(0.5f, 0.5f));

}

void SampleScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void SampleScene::Update() {

	// 
	// シーンの更新処理ここから
	// 

	if (SUGER::PushKey(DIK_D)) {
		// スプライトを回転
		pronama_chan.SetRotation(pronama_chan.GetRotation() + 0.01f);
		// モデルをy軸+方向に回転
		sample_.SetRotate(Vector3(sample_.GetRotate().x, sample_.GetRotate().y + 0.01f, sample_.GetRotate().z));

	} else if (SUGER::PushKey(DIK_A)) {
		// スプライトを回転
		pronama_chan.SetRotation(pronama_chan.GetRotation() - 0.01f);
		// モデルをy軸+方向に回転
		sample_.SetRotate(Vector3(sample_.GetRotate().x, sample_.GetRotate().y - 0.01f, sample_.GetRotate().z));
	}


	// 
	// シーンの更新処理ここまで
	//

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}
