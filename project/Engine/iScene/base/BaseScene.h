#pragma once

// C++
#include <memory>
#include <optional>

// MyHedder
#include "3d/cameras/camera/Camera.h"
#include "3d/lights/punctualLight/PunctualLight.h"
#include "transition/fade/Fade.h"
#include "enum/SceneEnum.h"

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
	void Update();

	// シーンマネージャのセット
	virtual void SetSceneManager(SceneManager* sceneManager);

protected:
	// ベースシーンの状態初期化処理
	void SceneStatusInitizlize();
	// ベースシーンの状態更新処理
	void SceneStatusUpdate();

	// フェードイン初期化
	virtual void SceneStatusFadeInInitialize();
	// フェードイン更新
	virtual void SceneStatusFadeInUpdate();

	// プレイフェーズ初期化
	virtual void SceneStatusPlayInitialize() = 0;
	// プレイフェーズ更新
	virtual void SceneStatusPlayUpdate() = 0;

	// フェードアウト初期化
	virtual void SceneStatusFadeOutInitialize();
	// フェードアウト更新
	virtual void SceneStatusFadeOutUpdate();

private:
	// カメラのImGui
	void ImGuiForDebugCamera();

private:
	// シーンマネージャ
	SceneManager* sceneManager_ = nullptr;

protected:
	// シーンのフェーズ
	SceneStatus sceneStatus_ = SceneStatus::kFadeIn;
	// 次のフェーズリスト
	std::optional<SceneStatus> sceneStatusRequest_ = std::nullopt;

	// デバッグカメラ
	std::unique_ptr<Camera> debugCamera_;
	// ライト
	std::unique_ptr<PunctualLight> light_;
	// フェード
	std::unique_ptr<Fade> fade_;

	// カメラ制御用のトランスフォーム
	Vector3 cameraRotate_;
	Vector3 cameraTranslate_;
};