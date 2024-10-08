// This
#include "MyGame.h"

// MyHedder
#include "debugTools/logger/Logger.h"


MyGame::~MyGame() {
}

void MyGame::Initialize() {
	// 基底システムの初期化
	SUGER::Initialize();

	// シーンファクトリ生成
	sceneFactory_ = std::make_unique<SceneFactory>();
	// シーンマネージャ作成
	sceneManager_ = std::make_unique<SceneManager>();
	// シーンマネージャにシーンファクトリをセット
	sceneManager_->SetSceneFactory(sceneFactory_.get());
	// 初期シーンのセット
	sceneManager_->ChangeScene("SAMPLE");
}

void MyGame::Finalize() {
	// ゲーム固有の終了処理

	// 基底システムの終了
	SUGER::Finalize();
}

void MyGame::Update() {
	// 基底システムの更新
	SUGER::Update();
	// シーンの更新処理
	sceneManager_->Update();
}

void MyGame::Draw() {
	// 基底システムの描画後処理
	SUGER::PreDraw();
	// シーンの描画処理
	sceneManager_->Draw();
	// 基底システムの描画後処理
	SUGER::PostDraw();
}
