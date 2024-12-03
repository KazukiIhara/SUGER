#include "BaseScene.h"

#include "framework/SUGER.h"
#include "imgui.h"
#include "debugTools/logger/Logger.h"
#include "manager/scene/SceneManager.h"

void BaseScene::Initialize() {
	// オブジェクトコンテナのクリア
	// Emitter
	SUGER::ClearEmitterContainer();
	// Particle
	SUGER::ClearParticleContainer();
	// Entity
	SUGER::ClearEntityContainer();
	// Empty
	SUGER::ClearEmptyContainer();
	// 2DObject
	SUGER::Clear2DObjectContainer();
	// デバッグログ
	Logger::Log("AllObjetcsCleared\n");

	// デバッグカメラ作成
	debugCamera_ = std::make_unique<Camera>();
	debugCamera_->Initialize();

	// ライト作成
	light_ = std::make_unique<PunctualLight>();
	light_->Initialize();

	// フェード作成
	fade_ = std::make_unique<Fade>();
	// フェード初期化
	fade_->Initialize();
	// フェードインリクエスト
	sceneStateRequest_ = SceneState::kFadeIn;

	// シーンに必要なカメラとライトのセット
	SUGER::SetRequiredObjects(debugCamera_.get(), light_.get());

	// FixFPSを初期化
	SUGER::FiXFPSInitialize();

}

void BaseScene::Update() {
	// キーボード入力でカメラフラグ切り替え
	if (SUGER::TriggerKey(DIK_P)) {
		if (isActiveDebugCamera_) {
			isActiveDebugCamera_ = false;
			SUGER::SetSceneCamera(sceneCamera_.get());
		} else {
			isActiveDebugCamera_ = true;
			SUGER::SetSceneCamera(debugCamera_.get());
		}
	}
	// ImGuiによるデバッグカメラコントロール
	DebugCameraState();
	// デバッグカメラのアップデート
	debugCamera_->Update();
	// ライトの更新
	light_->Update();
	// シーンステータスのリクエスト初期化処理
	SceneStatusInitizlize();
	// シーンステータスの更新処理
	SceneStatusUpdate();
}

void BaseScene::ChangeScene(const std::string& nextScene) {
	sceneManager_->ChangeScene(nextScene);
}

void BaseScene::SetSceneManager(SceneManager* sceneManager) {
	sceneManager_ = sceneManager;
}

void BaseScene::DebugCameraState() {
#ifdef _DEBUG
	// 回転と移動量を持ってくる
	Vector3 cameraRotate_ = debugCamera_->GetRotate();
	Vector3 cameraTranslate_ = debugCamera_->GetTranslate();

	// ImGuiの処理
	ImGui::Begin("DebugCamera");
	// デバッグカメラが有効なら
	if (isActiveDebugCamera_) {
		ImGui::Text("State: Enable");
		if (ImGui::Button("DisableDebugCamera")) {
			isActiveDebugCamera_ = false;
		}
		ImGui::DragFloat3("Rotate", &cameraRotate_.x, 0.01f);
		ImGui::DragFloat3("Translate", &cameraTranslate_.x, 0.01f);
	} else {
		ImGui::Text("State: Disable");
		if (ImGui::Button("EnableDebugCamera")) {
			isActiveDebugCamera_ = true;
		}
	}
	ImGui::End();

	// 回転と移動量を返す
	debugCamera_->SetRotate(cameraRotate_);
	debugCamera_->SetTranslate(cameraTranslate_);
#endif // _DEBUG
}

void BaseScene::SceneStatusInitizlize() {
	// シーンの状態
	if (sceneStateRequest_) {
		// 振る舞いを変更する
		sceneState_ = sceneStateRequest_.value();
		// 各振る舞いごとの初期化を実行
		switch (sceneState_) {
		case SceneState::kFadeIn:
			SceneStateFadeInInitialize();
			break;
		case SceneState::kPlay:
			SceneStatePlayInitialize();
			break;
		case SceneState::kFadeOut:
			SceneStateFadeOutInitialize();
			break;
		}
		// 振る舞いリクエストをリセット
		sceneStateRequest_ = std::nullopt;
	}
}

void BaseScene::SceneStatusUpdate() {
	switch (sceneState_) {
	case kFadeIn:
		SceneStateFadeInUpdate();
		break;
	case kPlay:
		SceneStatePlayUpdate();
		break;
	case kFadeOut:
		SceneStateFadeOutUpdate();
		break;
	}
}

void BaseScene::SceneStateFadeInInitialize() {
	// フェード開始
	fade_->Start(FadeStatus::FadeIn, 0.5f);
}

void BaseScene::SceneStateFadeInUpdate() {
	// フェード更新
	fade_->Update();

	if (fade_->IsFinished()) {
		sceneStateRequest_ = SceneState::kPlay;
		fade_->Stop();
	}
}

void BaseScene::SceneStateFadeOutInitialize() {
	// フェード開始
	fade_->Start(FadeStatus::FadeOut, 0.5f);
}

void BaseScene::SceneStateFadeOutUpdate() {
	// フェード更新
	fade_->Update();

	if (fade_->IsFinished()) {
		fade_->Stop();
		// ここに遷移先を指定したシーンチェンジ関数を呼び出す

	}
}
