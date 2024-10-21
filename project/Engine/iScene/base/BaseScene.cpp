#include "BaseScene.h"

#include "framework/SUGER.h"
#include "imgui.h"

void BaseScene::Initialize() {
	// カメラ作成
	debugCamera_ = std::make_unique<Camera>();
	debugCamera_->Initialize();
	// カメラの初期位置を設定
	debugCamera_->SetTranslate(kDefaultCameraTranslate_);
	debugCamera_->SetRotate(kDefaultCameraRotate_);

	// ライト作成
	light_ = std::make_unique<PunctualLight>();
	light_->Initialize();

	// シーンに必要なカメラとライトのセット
	SUGER::SetRequiredObjects(debugCamera_.get(), light_.get());
}

void BaseScene::Update() {
#ifdef _DEBUG
	// ImGuiによるデバッグカメラコントロール
	ImGuiForSceneCamera();
#endif // _DEBUG

	// カメラの更新処理
	CameraUpdate();

	// ライトの更新
	light_->Update();
}

void BaseScene::ImGuiForSceneCamera() {
	ImGui::Begin("DebugCamera");
	ImGui::DragFloat3("Rotate", &cameraRotate_.x, 0.01f);
	ImGui::DragFloat3("Translate", &cameraTranslate_.x, 0.01f);
	ImGui::End();
}

void BaseScene::CameraUpdate() {
	debugCamera_->SetRotate(cameraRotate_);
	debugCamera_->SetTranslate(cameraTranslate_);
	debugCamera_->Update();
}
