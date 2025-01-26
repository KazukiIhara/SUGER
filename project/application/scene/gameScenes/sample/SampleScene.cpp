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

	// 
	// シーンの初期化処理ここから
	// 

	// ティーポット
	// 初期トランスフォームを設定
	EulerTransform3D teapotDefaultTransform;
	teapotDefaultTransform.rotate = { 0.0f,0.0f,0.0f };
	teapotDefaultTransform.scale = { 1.0f,1.0f,1.0f };
	teapotDefaultTransform.translate = { 0.0f,1.0f,0.0f };
	// teapot作成
	teapot_ = std::make_unique<Teapot>();
	teapot_->Initialize(SUGER::CreateEntity("teapot", "Sphere", teapotDefaultTransform));

	terrain_ = std::make_unique<EntityController>();
	terrain_->Initialize(SUGER::CreateEntity("terrain", "terrain"));

	

	//
	// GrobalData
	//

}

void SampleScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void SampleScene::SceneStatePlayInitialize() {

}

void SampleScene::SceneStatePlayUpdate() {


}