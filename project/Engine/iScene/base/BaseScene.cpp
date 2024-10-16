#include "BaseScene.h"

#include "framework/SUGER.h"
#include "imgui.h"

void BaseScene::Initialize() {
	// カメラ作成
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	// カメラの初期位置を設定
	camera_->SetTranslate(kDefaultCameraTranslate_);
	camera_->SetRotate(kDefaultCameraRotate_);

	// ライト作成
	light_ = std::make_unique<PunctualLight>();
	light_->Initialize();

	// シーンに必要なカメラとライトのセット
	SUGER::SetRequiredObjects(camera_.get(), light_.get());
}

void BaseScene::Update() {
#ifdef _DEBUG
	// ImGuiによるカメラコントロール
	ImGuiForSceneCamera();
#endif // _DEBUG

	// カメラの更新処理
	CameraUpdate();

	// ライトの更新
	light_->Update();
}

void BaseScene::ImGuiForSceneCamera() {
	ImGui::Begin("SceneCamera");
	ImGui::DragFloat3("Rotate", &cameraRotate_.x, 0.01f);
	ImGui::DragFloat3("Translate", &cameraTranslate_.x, 0.01f);
	ImGui::End();
}

void BaseScene::CameraUpdate() {
	camera_->SetRotate(cameraRotate_);
	camera_->SetTranslate(cameraTranslate_);
	camera_->Update();
}
