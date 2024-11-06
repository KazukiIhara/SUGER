#include "Player.h"

#include "framework/SUGER.h"

void Player::Initialize() {
	// プレイヤー作成
	SUGER::Create3DObject("Player", "Player");
	// オブジェクト3dコントローラを初期化 
	player_.Initialize(SUGER::FindObject3D("Player"));

	// 照準作成
	SUGER::Create2DObject("Reticle", "Reticle");
	// 照準のコントローラを初期化
	reticle_.Initialize(SUGER::FindObject2D("Reticle"));

}

void Player::Update() {
}

void Player::SetRailTransform(WorldTransform* railTransform) {
	player_.SetParent(railTransform);
}