#include "CG3Scene.h"

// MyHedder
#include "framework/SUGER.h"
#include "debugTools/logger/Logger.h"

void CG3Scene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();

	sceneCamera_->SetRotate(Vector3(0.0f, 0.0f, 0.0f));
	sceneCamera_->SetTranslate(Vector3(0.0f, 0.0f, -2.5f));

	// 
	// シーンの初期化処理ここから
	// 

	// 爆発エフェクト初期化
	explosion_.Initialize();
}

void CG3Scene::Finalize() {
	// デバッグ用文字
	Logger::Log("EffectScene,Finalized\n");

}

void CG3Scene::SceneStatePlayInitialize() {

}

void CG3Scene::SceneStatePlayUpdate() {

	ImGui::Begin("EffectScene");
	ImGui::Text("PUSH SPACE To Emit");
	ImGui::End();

	// スペースを押したら発生
	if (SUGER::TriggerKey(DIK_SPACE)) {
		explosion_.Emit();
	}
	// 爆発エフェクト更新
	explosion_.Update();
}
