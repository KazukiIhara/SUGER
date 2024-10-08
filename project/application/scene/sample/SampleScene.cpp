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
	
	uvChecker_ = std::make_unique<Sprite>();
	uvChecker_->Initialize("resources/images/uvChecker.png");

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

	uvChecker_->Update();
}

void SampleScene::Draw() {

	SUGER::PreDrawObject2D();
	uvChecker_->Draw();
}