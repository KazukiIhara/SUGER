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

	// カメラの設定
	sceneCamera_ = std::make_unique<Camera>();
	sceneCamera_->Initialize();

	// シーンにカメラをセット
	//SUGER::SetSceneCamera(sceneCamera_.get());

	// サウンド読み込み
	SUGER::LoadWaveSound("Alarm01.wav");

	// 板ポリパーティクルの作成
	SUGER::CreateFixParticle("circle", ParticleType::kPlane, "circle.png");
	// エミッターの作成
	SUGER::CreateEmitter("sampleEmitter");

	// エンティティの作成とエンティティコントローラ初期化
	entity_.Initialize(SUGER::CreateEntity("teapot", "pronama_chan"));
	// ライトを無効化
	entity_.SetEnableLight(false);

	// オブジェクト2Dの作成とコントローラの初期化
	pronama_chan.Initialize(SUGER::Create2DObject("pronama_chan", "pronama_chan.png"));

	// オブジェクト2Dコントローラを使ってポジションとアンカーポイントをセット
	pronama_chan.SetSize(Vector2(400.0f, 400.0f));
	pronama_chan.SetPosition(pronama_chan.GetSize() / 2.0f);
	pronama_chan.SetAnchorPoint(Vector2(0.5f, 0.5f));

	// エミッターのコントローラを初期化
	emitter_.Initialize("sampleEmitter");
	// エミッターにパーティクルをセット
	emitter_.SetParticle("circle");
	// エミッターの発生個数を変更
	emitter_.SetCount(5);

	emitter_.SetIsRandom(true);
	emitter_.SetIsRepeat(true);

	//
	// GrobalData
	//

	// プロ生ちゃんのデータグループを作成
	SUGER::AddGrobalDataGroup("Pronama_Chan");
	// グローバルデータのプロ生ちゃんグループにトランスレート情報を追加
	SUGER::AddGrobalDataItem("Pronama_Chan", "translate", entity_.GetTranslate());
}

void SampleScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void SampleScene::SceneStatusPlayInitialize() {


}

void SampleScene::SceneStatusPlayUpdate() {

	//
	// GrobalData
	//

	// 更新処理の初めにグローバルデータクラスに保存されている値を取得
	entity_.SetTranslate(SUGER::GetGrobalDataValueVector3("Pronama_Chan", "translate"));

	// 
	// シーンの更新処理ここから
	// 

	// スペースキーを押すと発生
	if (SUGER::PushKey(DIK_SPACE)) {
		emitter_.Emit();
	}

	if (SUGER::PushKey(DIK_D)) {
		// スプライトを回転
		pronama_chan.SetRotation(pronama_chan.GetRotation() + 0.01f);
		entity_.SetTranslate(Vector3(entity_.GetTranslate().x + 0.1f, entity_.GetTranslate().y, entity_.GetTranslate().z));
	} else if (SUGER::PushKey(DIK_A)) {
		// スプライトを回転
		pronama_chan.SetRotation(pronama_chan.GetRotation() - 0.01f);
		entity_.SetTranslate(Vector3(entity_.GetTranslate().x - 0.1f, entity_.GetTranslate().y, entity_.GetTranslate().z));
	}


	// 
	// シーンの更新処理ここまで
	//


	//
	// GrobalData
	//

	// 行列更新の手前でローカルデータをグローバルデータクラスに挿入
	SUGER::SetGrobalDataValue("Pronama_Chan", "translate", entity_.GetTranslate());

}