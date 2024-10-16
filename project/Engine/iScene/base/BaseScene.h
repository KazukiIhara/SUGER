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

	// シーンマネージャのセット
	virtual void SetSceneManager(SceneManager* sceneManager) {
		sceneManager_ = sceneManager;
	}

private:
	// カメラのImGui
	void ImGuiForSceneCamera();

	// カメラの更新
	void CameraUpdate();

private:
	// シーンマネージャ
	SceneManager* sceneManager_ = nullptr;

	// カメラ
	std::unique_ptr<Camera> camera_;
	// ライト
	std::unique_ptr<PunctualLight> light_;

protected:
	// カメラの初期トランスフォーム
	const Vector3 kDefaultCameraRotate_ = { 0.45f,0.0f,0.0f };
	const Vector3 kDefaultCameraTranslate_ = { 0.0f,5.0f,-10.0f };

	// カメラ制御用のトランスフォーム
	Vector3 cameraRotate_ = kDefaultCameraRotate_;
	Vector3 cameraTranslate_ = kDefaultCameraTranslate_;
};