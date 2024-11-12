// This
#include "ShootingCoasterScene.h"

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "framework/SUGER.h"
#include "debugTools/logger/Logger.h"


void ShootingCoasterScene::Initialize() {
	// シーンの初期化(初期化処理の先頭)
	BaseScene::Initialize();

	// 
	// シーンの初期化処理ここから
	// 
	railCamera_ = std::make_unique<RailCamera>();
	railCamera_->Initialize();

	SUGER::SetSceneCamera(railCamera_.get());

	// JsonDataの読み込み
	SUGER::LoadJsonLevelData("ShootingCoaster");

	// JsonDataをシーンにインポート
	jsonImporter_.ImportLevel(SUGER::FindJsonLevelData("ShootingCoaster"), railCamera_.get(), baroons_);

	// プレイヤーの生成と初期化
	player_ = std::make_unique<Player>();
	player_->Initialize();
	player_->SetRailTransform(railCamera_->GetWorldTransformPtr());

}

void ShootingCoasterScene::Finalize() {
	// デバッグ用文字
	Logger::Log("SampleScene,Finalized\n");

}

void ShootingCoasterScene::Update() {

	// 
	// シーンの更新処理ここから
	// 

	// プレイヤーの更新
	player_->Update();

	railCamera_->SetSpeed(player_->GetRotateX());

	// レールカメラの更新
	railCamera_->Update();

	// コライダーリストの初期化
	SUGER::ResetColliderList();
	// プレイヤーの球リストをコライダーリストに追加
	player_->SetColliderListBullet();

	// baroonをコライダーに追加
	for (const std::unique_ptr<Baroon>& baroon : baroons_) {
		SUGER::AddCollider(baroon.get());
	}

	// 
	// シーンの更新処理ここまで
	//

	// シーンの更新(更新処理の最後)
	BaseScene::Update();
}
