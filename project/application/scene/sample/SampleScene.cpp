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

	cameraTransform_.Initialize();
	cameraTransform_.translate.z = -10.0f;
	camera_ = std::make_unique<Camera>();
	camera_->Initialize(&cameraTransform_);

	light_ = std::make_unique<PunctualLight>();
	light_->Initialize();

	sampleTexture_ = std::make_unique<Sprite>();
	sampleTexture_->Initialize("resources/images/nero.jpg ");

	SUGER::LoadModel("teapot");

	sampleObject_ = std::make_unique<Object3D>();
	sampleObject_->SetModel("teapot");
	sampleObject_->SetViewProjection(camera_->GetViewProjectionMatrix());
	sampleObject_->SetPunctualLight(light_.get());
	sampleObject_->Initialize();

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

	sampleObject_->Update();
}

void SampleScene::Draw() {

	// 3Dオブジェクト描画前処理
	SUGER::PreDrawObject3D();
	sampleObject_->Draw();

	// 2Dオブジェクト描画前処理
	SUGER::PreDrawObject2D();
	sampleTexture_->Draw();

}