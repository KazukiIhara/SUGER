#pragma once

// C++
#include <memory>

// MyHedder
#include "3d/cameras/camera/Camera.h"
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

	// シーンマネージャのセット
	virtual void SetSceneManager(SceneManager* sceneManager) {
		sceneManager_ = sceneManager;
	}

private:
	// カメラのImGui
	void ImGuiForSceneCamera();

private:
	// シーンマネージャ
	SceneManager* sceneManager_ = nullptr;

protected:
	// カメラ
	std::unique_ptr<Camera> debugCamera_;
	// ライト
	std::unique_ptr<PunctualLight> light_;

	// カメラ制御用のトランスフォーム
	Vector3 cameraRotate_;
	Vector3 cameraTranslate_;
};