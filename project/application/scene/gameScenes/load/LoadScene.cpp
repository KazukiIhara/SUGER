#include "LoadScene.h"

#include "framework/SUGER.h"
#include "debugTools/logger/Logger.h"

void LoadScene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();

}

void LoadScene::Finalize() {
	Logger::Log("AllResources,Loaded");
}

void LoadScene::SceneStatePlayInitialize() {

}

void LoadScene::SceneStatePlayUpdate() {

	// ロードシーンにリクエストに応じて初期化
	LoadSceneStateInitialize();
	// ロードシーン状態に応じて更新
	LoadSceneStateUpdate();
}

void LoadScene::LoadSceneStateInitialize() {
	// ロードシーンの状態
	if (loadSceneStateRequest_) {
		// 振る舞いを変更
		loadSceneState_ = loadSceneStateRequest_.value();
		// 状態ごとの初期化を実行
		switch (loadSceneState_) {
		case LoadScene::kPreLoad:
			LoadSceneStatePreLoadInitialize();
			break;
		case LoadScene::kLoading:
			LoadSceneStateLoadingInitialize();
			break;
		case LoadScene::kFinished:
			LoadSceneStateFinishedInitizlize();
			break;
		}

	}
}

void LoadScene::LoadSceneStateUpdate() {
	switch (loadSceneState_) {
		case LoadScene::kPreLoad:
			LoadSceneStatePreLoadUpdate();
			break;
		case LoadScene::kLoading:
			LoadSceneStateLoadingUpdate();
			break;
		case LoadScene::kFinished:
			LoadSceneStateFinishedUpdate();
			break;
	}
}

void LoadScene::LoadSceneStatePreLoadInitialize() {


}

void LoadScene::LoadSceneStatePreLoadUpdate() {

}

void LoadScene::LoadSceneStateLoadingInitialize() {
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

void LoadScene::LoadSceneStateLoadingUpdate() {

}

void LoadScene::LoadSceneStateFinishedInitizlize() {

}

void LoadScene::LoadSceneStateFinishedUpdate() {

}
