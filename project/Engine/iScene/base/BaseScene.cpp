#include "BaseScene.h"

#include "framework/SUGER.h"
#include "imgui.h"

void BaseScene::Initialize() {
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
	// フェードイン
	sceneStatusRequest_ = SceneStatus::kFadeIn;

	// シーンに必要なカメラとライトのセット
	SUGER::SetRequiredObjects(debugCamera_.get(), light_.get());
}

void BaseScene::Update() {
	// ImGuiによるデバッグカメラコントロール
	ImGuiForDebugCamera();
	// デバッグカメラのアップデート
	debugCamera_->Update();
	// ライトの更新
	light_->Update();

	// シーンステータスのリクエスト初期化処理
	SceneStatusInitizlize();
	// シーンステータスのリクエスト更新処理
	SceneStatusUpdate();

}

void BaseScene::ImGuiForDebugCamera() {
#ifdef _DEBUG
	// 回転と移動量を持ってくる
	cameraRotate_ = debugCamera_->GetRotate();
	cameraTranslate_ = debugCamera_->GetTranslate();

	// ImGuiの処理
	ImGui::Begin("DebugCamera");
	ImGui::DragFloat3("Rotate", &cameraRotate_.x, 0.01f);
	ImGui::DragFloat3("Translate", &cameraTranslate_.x, 0.01f);
	ImGui::End();

	// 回転と移動量を返す
	debugCamera_->SetRotate(cameraRotate_);
	debugCamera_->SetTranslate(cameraTranslate_);
#endif // _DEBUG
}

void BaseScene::SceneStatusInitizlize() {
	// シーンの状態
	if (sceneStatusRequest_) {
		// 振る舞いを変更する
		sceneStatus_ = sceneStatusRequest_.value();
		// 各振る舞いごとの初期化を実行
		switch (sceneStatus_) {
			case SceneStatus::kFadeIn:
				SceneStatusFadeInInitialize();
				break;
			case SceneStatus::kPlay:
				SceneStatusPlayInitialize();
				break;
			case SceneStatus::kFadeOut:
				SceneStatusFadeOutInitialize();
				break;
		}
		// 振る舞いリクエストをリセット
		sceneStatusRequest_ = std::nullopt;
	}
}

void BaseScene::SceneStatusUpdate() {
	switch (sceneStatus_) {
		case kFadeIn:
			SceneStatusFadeInUpdate();
			break;
		case kPlay:
			SceneStatusPlayUpdate();
			break;
		case kFadeOut:
			SceneStatusFadeOutUpdate();
			break;
	}
}

void BaseScene::SceneStatusFadeInInitialize() {
	// フェード開始
	fade_->Start(FadeStatus::FadeIn, 2.0f);
}

void BaseScene::SceneStatusFadeInUpdate() {
	// フェード更新
	fade_->Update();

	if (fade_->IsFinished()) {
		sceneStatus_ = SceneStatus::kPlay;
		fade_->Stop();
	}
}

void BaseScene::SceneStatusFadeOutInitialize() {
	// フェード開始
	fade_->Start(FadeStatus::FadeOut, 2.0f);
}

void BaseScene::SceneStatusFadeOutUpdate() {
	// フェード更新
	fade_->Update();

	if (fade_->IsFinished()) {
		sceneStatus_ = SceneStatus::kPlay;
		fade_->Stop();
	}
}
