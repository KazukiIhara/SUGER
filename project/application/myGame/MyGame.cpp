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
	sceneManager_->ChangeScene("SHOOTINGCOASTER");
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
	// 2DObjectの更新
	SUGER::Update2DObjects();
	// 3DObjectの更新
	SUGER::Update3DObjects();
	// Particleの更新
	SUGER::UpdateParticle();
}

void MyGame::Draw() {
	// 描画前処理
	SUGER::PreDraw();
	// 描画処理
	SUGER::Draw();
	// 描画後処理
	SUGER::PostDraw();
}
