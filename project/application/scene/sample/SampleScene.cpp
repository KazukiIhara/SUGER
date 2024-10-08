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

	sampleTexture_ = std::make_unique<Sprite>();
	sampleTexture_->Initialize("resources/images/nero.jpg ");

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

	sampleTexture_->Update();
}

void SampleScene::Draw() {

	SUGER::PreDrawObject2D();
	sampleTexture_->Draw();
}