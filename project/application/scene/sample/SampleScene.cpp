// This
#include "SampleScene.h"

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "framework/SUGER.h"
#include "debugTools/logger/Logger.h"


void SampleScene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();

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


	sampleTexture_->Update();

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}

void SampleScene::Draw() {
	// 2Dオブジェクト描画前処理
	SUGER::PreDrawObject2D();
	sampleTexture_->Draw();

}