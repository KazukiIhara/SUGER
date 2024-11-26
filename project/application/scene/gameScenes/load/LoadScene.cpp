#include "LoadScene.h"

#include "framework/SUGER.h"
#include "debugTools/logger/Logger.h"

void LoadScene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();
	// サウンド読み込み
	SUGER::LoadWaveSound("Alarm01.wav");

	// テクスチャ読み込み
	// テクスチャの規定ディレクトリパス
	const std::string textureDirectoryPath = "resources/images/";

	SUGER::LoadTexture(textureDirectoryPath + "myUvChecker.png");
	SUGER::LoadTexture(textureDirectoryPath + "circle.png");
	SUGER::LoadTexture(textureDirectoryPath + "pronama_chan.png");

	// モデル読み込み
	const std::string modelDirectoryPath = "resources/models/";
	SUGER::LoadModel(modelDirectoryPath + "pronama_chan");
}

void LoadScene::Finalize() {
	Logger::Log("AllResources,Loaded");
}

void LoadScene::SceneStatusPlayInitialize() {
	
}

void LoadScene::SceneStatusPlayUpdate() {

}

void LoadScene::LoadSceneStateInitialize() {
	// ロードシーンの状態
	if (loadSceneStateRequest_) {
		// 振る舞いを変更
		loadSceneState_ = loadSceneStateRequest_.value();
		// 状態ごとの初期化を実行
		switch (loadSceneState_) {
		case LoadScene::kLoad:
			
			break;
		case LoadScene::kFinished:

			break;
		}

	}
}

void LoadScene::LoadSceneStateUpdate() {
	  
}

void LoadScene::LoadSceneLoadInitialize() {
}

void LoadScene::LoadSceneLoadUpdate() {
}

void LoadScene::LoadSceneFinishedInitizlize() {
}

void LoadScene::LoadSceneFinishedUpdate() {
}
 