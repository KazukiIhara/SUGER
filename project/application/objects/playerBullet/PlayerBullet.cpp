#include "PlayerBullet.h"
#include "framework/SUGER.h"

#include "objects/player/Player.h"

void PlayerBullet::Initialize(const Vector3& position, const Vector3& velocity, Player* player) {
	// 弾を作成
	const std::string objectName = SUGER::Create3DObject("Bullet", "Bullet", EulerTransform3D(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), position));
	// 移動量を代入
	velocity_ = velocity;
	// コントローラの初期化
	controller_.Initialize(SUGER::FindObject3D(objectName));
	// 回転を移動量から計算
	controller_.SetRotate(Vector3(
		std::atan2(-velocity_.y, std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z)),
		std::atan2(velocity_.x, velocity_.z),
		0.0f
	));
	controller_.SetIsDelete(false);
	isDead_ = false;
	SetCategory(kPlayerBullet);
	// コライダーの半径を設定
	SetRadius(0.5f);

	player_ = player;
}

void PlayerBullet::Update() {
	/*座標を移動*/
	controller_.SetTranslate(controller_.GetTranslate() + velocity_);
	/*経過時間でDeath*/
	if (--deathTimer_ <= 0) {
		isDead_ = true;
		controller_.SetIsDelete(true);
	}
}

bool PlayerBullet::GetIsDead() {
	return isDead_;
}

void PlayerBullet::OnCollision(Collider* other) {
	// 衝突相手のカテゴリを取得
	ColliderCategory category = other->GetCategory();

	switch (category) {
	case kNone:
		break;
	case kPlayerBullet:
		break;
	case kBaroon:
		player_->PlusScore();
		isDead_ = true;
		controller_.SetIsDelete(true);
		break;
	default:
		break;
	}
}
