// This
#include "SampleScene.h"

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "framework/SUGER.h"
#include "debugTools/logger/Logger.h"


void SampleScene::Initialize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Initialized\n");

	// カメラ作成
	cameraTransform_.Initialize();
	cameraTransform_.translate.z = -10.0f;
	camera_ = std::make_unique<Camera>();
	camera_->Initialize(&cameraTransform_);

	// ライト作成
	light_ = std::make_unique<PunctualLight>();
	light_->Initialize();

	// シーンに必要なカメラとライトのセット
	SUGER::SetRequiredObjects(camera_.get(), light_.get());

	sampleTexture_ = std::make_unique<Sprite>();
	sampleTexture_->Initialize("resources/images/nero.jpg ");

	// オブジェクトの作成
	SUGER::Create3DObject("teapot", "teapot");

}

void SampleScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void SampleScene::Update() {
#ifdef _DEBUG
	ImGui::Begin("SampleScene Update");
	ImGui::End();
#endif // _DEBUG
	camera_->Update();
	light_->SetCameraPosition(*camera_->GetWorldPos());
	light_->Update();

	sampleTexture_->Update();
}

void SampleScene::Draw() {
	// 2Dオブジェクト描画前処理
	SUGER::PreDrawObject2D();
	sampleTexture_->Draw();

}