#include "BaseScene.h"
#include "manager/scene/SceneManager.h"

#include "framework/SUGER.h"
#include "imgui.h"

void BaseScene::Initialize() {
	// カメラ作成
	debugCamera_ = std::make_unique<Camera>();
	debugCamera_->Initialize();

	// ライト作成
	light_ = std::make_unique<PunctualLight>();
	light_->Initialize();

	// シーンに必要なカメラとライトのセット
	SUGER::SetRequiredObjects(debugCamera_.get(), light_.get());

	// Objectコンテナをクリア
	SUGER::Clear3DObjects();
	SUGER::Clear2DObjects();

	// コライダーリストをリセット
	SUGER::ResetColliderList();
	// FiXFPSシステムをリセット
	SUGER::ResetFixFPS();
}

void BaseScene::Update() {
	// ImGuiによるデバッグカメラコントロール
	ImGuiForDebugCamera();


	// デバッグカメラのアップデート
	debugCamera_->Update();

	// ライトの更新
	light_->Update();
}

void BaseScene::ChangeScene(const std::string& necxtScene) {
	sceneManager_->ChangeScene(necxtScene);
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