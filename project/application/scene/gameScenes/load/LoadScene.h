#pragma once

// Common
#include "iScene/base/BaseScene.h"
#include "2d/controller/Object2dController.h"
#include "3d/entityController/EntityController.h"
#include "particle/emitterController/EmitterController.h"

class LoadScene:public BaseScene {
public:
	enum LoadSceneState {
		kLoad,
		kFinished,
	};
	LoadScene() = default;
	~LoadScene() = default;

	// 初期化
	void Initialize()override;
	// 終了
	void Finalize()override;

	// プレイフェーズ初期化
	void SceneStatusPlayInitialize()override;
	// プレイフェーズ更新
	void SceneStatusPlayUpdate()override;

	// ロードシーン状態初期化
	void LoadSceneStateInitialize();
	// ロードシーン状態更新
	void LoadSceneStateUpdate();

	// ロード状態初期化
	void LoadSceneLoadInitialize();
	// ロード状態更新
	void LoadSceneLoadUpdate();

	// ロード終了状態初期化
	void LoadSceneFinishedInitizlize();
	// ロード終了状態更新
	void LoadSceneFinishedUpdate();

private:
	// ロードシーンのフェーズ
	LoadSceneState loadSceneState_ = LoadSceneState::kLoad;
	// 次のロードシーンのフェーズ
	std::optional<LoadSceneState> loadSceneStateRequest_ =std::nullopt;

};