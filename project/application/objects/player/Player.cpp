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

	reticleTransform_.Initialize();

	// 弾のモデル読み込み
	SUGER::LoadModel("Bullet");
}

void Player::Update() {

	/*デスフラグの立った弾を削除*/
	bullets_.remove_if([](PlayerBullet* bullet) {
		if (bullet->GetIsDead()) {
			delete bullet;
			return true;
		}
		return false;
		});

	// 照準の操作
	MoveReticle();

	// 照準の座標変換
	ScreenToWorld();

	// 攻撃処理
	Attack();

	// 弾更新
	for (PlayerBullet* bullet : bullets_) {
		bullet->Update();
	}
}

void Player::MoveReticle() {
	float s = static_cast<float>(SUGER::GetLeftStickX(0));
	// レティクルの操作
	reticlePosition_ = reticle_.GetPosition() + Vector2(static_cast<float>(SUGER::GetLeftStickX(0) / 1000.0f), -static_cast<float>(SUGER::GetLeftStickY(0) / 1000.0f));
	// 画面外へ行かないようにする処理
	reticlePosition_.x = std::clamp(reticlePosition_.x, 100.0f, static_cast<float>(WindowManager::kClientWidth) - 100.0f);
	reticlePosition_.y = std::clamp(reticlePosition_.y, 100.0f, static_cast<float>(WindowManager::kClientHeight) - 100.0f);
	// レティクルの値をセット
	reticle_.SetPosition(reticlePosition_);
}

void Player::ScreenToWorld() {
	/*ビュープロジェクションビューポート合成行列*/
	/*ビューポート行列*/
	Matrix4x4 matViewport = MakeViewportMatrix(0, 0, WindowManager::kClientWidth, WindowManager::kClientHeight, 0, 1);
	Matrix4x4 matVPV = player_.GetCamera()->GetViewProjectionMatrix() * matViewport;
	Matrix4x4 matInverseVPV = Inverse(matVPV);

	/*スクリーン座標*/
	Vector3 posNear = Vector3(static_cast<float>(reticlePosition_.x), static_cast<float>(reticlePosition_.y), 0);
	Vector3 posFar = Vector3(static_cast<float>(reticlePosition_.x), static_cast<float>(reticlePosition_.y), 1);

	/*スクリーン座標系からワールド座標系へ*/
	posNear = Transform(posNear, matInverseVPV);
	posFar = Transform(posFar, matInverseVPV);

	Vector3 reticleDirection = posFar - posNear;
	reticleDirection = Normalize(reticleDirection);

	reticleTransform_.translate_ = posNear + kDistanceReticle_ * reticleDirection;

	reticleTransform_.Update();
}

void Player::Attack() {
	// パッドのボタンを押したら
	if (SUGER::TriggerButton(0, ButtonA)) {
		// 弾の速度
		const float kBulletSpeed = 1.5f;
		Vector3 velocity(0, 0, kBulletSpeed);
		// 速度ベクトルを自機の向きに合わせて回転させる
		Vector3 reticleWorldPos = ExtractionWorldPos(reticleTransform_.worldMatrix_);
		Vector3 worldPos = ExtractionWorldPos(player_.GetWorldTransform()->worldMatrix_);
		velocity = reticleWorldPos - worldPos;
		velocity = kBulletSpeed * Normalize(velocity);
		// 弾を生成して初期化
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(worldPos, velocity);

		bullets_.push_back(newBullet);
	}
}

void Player::SetRailTransform(WorldTransform* railTransform) {
	player_.SetParent(railTransform);
}