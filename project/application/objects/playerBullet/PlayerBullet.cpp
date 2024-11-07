#include "PlayerBullet.h"
#include "framework/SUGER.h"

void PlayerBullet::Initialize(const Vector3& position, const Vector3& velocity) {
	// 弾を作成
	const std::string objectName = SUGER::Create3DObject("Bullet", "Bullet", EulerTransform3D(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), position));
	// 移動量を代入
	velocity_ = velocity;
	// コントローラの初期化
	bullet_.Initialize(SUGER::FindObject3D(objectName));
	// 回転を移動量から計算
	bullet_.SetRotate(Vector3(
		std::atan2(-velocity_.y, std::sqrt(velocity_.x * velocity_.x + velocity_.z * velocity_.z)),
		std::atan2(velocity_.x, velocity_.z),
		0.0f
	));
}

void PlayerBullet::Update() {
	/*座標を移動*/
	bullet_.SetTranslate(bullet_.GetTranslate() + velocity_);
	/*経過時間でDeath*/
	if (--deathTimer_ <= 0) {
		isDead_ = true;
		bullet_.SetIsDelete(true);
	}
}

bool PlayerBullet::GetIsDead() {
	return isDead_;
}
