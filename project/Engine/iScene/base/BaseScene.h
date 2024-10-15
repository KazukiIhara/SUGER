#pragma once

// C++
#include <memory>

// MyHedder
#include "3d/camera/Camera.h"
#include "3d/lights/punctualLight/PunctualLight.h"

// 前方宣言
class SceneManager;

// シーンの基底クラス
class BaseScene {
public: // 仮想関数
	// 仮想デストラクタ
	virtual ~BaseScene() = default;
	// 初期化
	virtual void Initialize();
	// 終了
	virtual void Finalize() = 0;
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw() = 0;

	// シーンマネージャのセット
	virtual void SetSceneManager(SceneManager* sceneManager) {
		sceneManager_ = sceneManager;
	}
private:
	// シーンマネージャ
	SceneManager* sceneManager_ = nullptr;
protected:
	// カメラ
	std::unique_ptr<Camera> camera_;
	WorldTransform cameraTransform_{};

	// ライト
	std::unique_ptr<PunctualLight> light_;
};