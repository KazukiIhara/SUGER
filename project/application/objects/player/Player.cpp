#include "Player.h"

#include "framework/SUGER.h"

void Player::Initialize() {
	// プレイヤー作成
	SUGER::Create3DObject("Player", "Player");
	// オブジェクト3dコントローラを初期化 
	player_.Initialize(SUGER::FindObject3D("Player"));
}

void Player::Update() {
}

void Player::SetRailTransform(WorldTransform* railTransform) {
	player_.SetParent(railTransform);
}
