#include "PlayerBullet.h"
#include "framework/SUGER.h"

void PlayerBullet::Initialize(const Vector3& position, const Vector3& velocity) {

	const std::string objectName = SUGER::Create3DObject("Bullet", "Bullet", EulerTransform3D(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), position));
	velocity_ = velocity;
	bullet_.Initialize(SUGER::FindObject3D(objectName));
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
