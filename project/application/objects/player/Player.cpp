#include "Player.h"

#include "framework/SUGER.h"

void Player::Initialize() {
	// プレイヤー作成
	SUGER::Create3DObject("Player", "Player");
	// オブジェクト3dコントローラを初期化 
	player_.Initialize(SUGER::FindObject3D("Player"));

	// 照準作成
	SUGER::Create2DObject("Reticle", "Reticle.png");
	// 照準のコントローラを初期化
	reticle_.Initialize(SUGER::FindObject2D("Reticle"));
	reticle_.SetAnchorPoint(Vector2(0.5f, 0.5f));
	reticle_.SetPosition(Vector2(WindowManager::kClientWidth / 2.0f, WindowManager::kClientHeight / 2.0f));
}

void Player::Update() {

	// 照準の操作
	MoveReticle();

	// 照準の座標変換
	ScreenToWorld();
}

void Player::MoveReticle() {
	float s = static_cast<float>(SUGER::GetLeftStickX(0));
	// レティクルの操作
	Vector2 reticlePosition = reticle_.GetPosition() + Vector2(static_cast<float>(SUGER::GetLeftStickX(0) / 1000.0f), -static_cast<float>(SUGER::GetLeftStickY(0) / 1000.0f));
	// 画面外へ行かないようにする処理
	reticlePosition.x = std::clamp(reticlePosition.x, 100.0f, static_cast<float>(WindowManager::kClientWidth) - 100.0f);
	reticlePosition.y = std::clamp(reticlePosition.y, 100.0f, static_cast<float>(WindowManager::kClientHeight) - 100.0f);
	// レティクルの値をセット
	reticle_.SetPosition(reticlePosition);
}

void Player::ScreenToWorld() {
	/*ビュープロジェクションビューポート合成行列*/
	/*ビューポート行列*/
	Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WindowManager::kClientWidth, WindowManager::kClientHeight, 0, 1);
	Matrix4x4 matVPV = player_.GetCamera()->GetViewProjectionMatrix() * matViewport;
	Matrix4x4 matInverseVPV = Inverse(matVPV);
}

void Player::SetRailTransform(WorldTransform* railTransform) {
	player_.SetParent(railTransform);
}