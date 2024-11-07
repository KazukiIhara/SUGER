#include "PlayerBullet.h"
#include "framework/SUGER.h"

void PlayerBullet::Initialize(const Vector3& position, const Vector3& velocity, const uint32_t bulletNum) {

	SUGER::Create3DObject("Bullet", "Bullet", EulerTransform3D(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), position));
	velocity_ = velocity;
}

void PlayerBullet::Update() {
	/*座標を移動*/
	bullet_.SetTranslate(bullet_.GetTranslate() + velocity_);
	/*経過時間でDeath*/
	if (--deathTimer_ <= 0) {
		bullet_.SetIsDelete(true);
	}
}