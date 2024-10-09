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

	SUGER::LoadModel("teapot");

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

	// 3Dオブジェクト描画前処理
	SUGER::PreDrawObject3D();


	// 2Dオブジェクト描画前処理
	SUGER::PreDrawObject2D();
	sampleTexture_->Draw();

}