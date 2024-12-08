#include "EvaluationTaskScene.h"

// MyHedder
#include "framework/SUGER.h"
#include "debugTools/logger/Logger.h"

void EvaluationScene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();

	// 
	// シーンの初期化処理ここから
	// 

	// 板ポリパーティクルの作成
	SUGER::CreateParticle("sampleParticle", ParticleType::kPlane, "uvChecker.png");
	// エミッターの作成
	SUGER::CreateEmitter("sampleEmitter");

	// エミッターのコントローラを初期化
	emitter_.Initialize("sampleEmitter");
	// エミッターにパーティクルをセット
	emitter_.SetParticle("sampleParticle");
	// エミッターの発生個数を変更
	emitter_.SetCount(10);
	// エミッターの発生タイプを設定
	emitter_.SetEmitType(kDefault);
	// ブレンドモードセット
	emitter_.SetBlendMode(kBlendModeNone);
	// 繰り返し発生オフ
	emitter_.SetIsRepeat(true);
}

void EvaluationScene::Finalize() {
	Logger::Log("EvaluationScene,Finalized");
}

void EvaluationScene::SceneStatePlayInitialize() {
	
}

void EvaluationScene::SceneStatePlayUpdate() {
	ImGui::Begin("EvaluationTaskScene");
	if (ImGui::Button("EffectScene")) {
		ChangeScene("CG3");
	}
	ImGui::End();
}
