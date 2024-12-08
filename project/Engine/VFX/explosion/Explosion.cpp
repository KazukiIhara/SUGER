#include "Explosion.h"

#include "framework/SUGER.h"

void Explosion::Initialize() {

	// 必要なエミッターとパーティクル作成
	SUGER::CreateParticle("fire", kPlane, "circle.png");
	SUGER::CreateParticle("smoke", kPlane, "circle.png");
	// fire
	fireEmitter_.Initialize(SUGER::CreateEmitter("fire"));
	fireEmitter_.SetParticle("fire");
	fireEmitter_.SetIsRepeat(false);
	fireEmitter_.SetCount(10);
	fireEmitter_.SetEmitType(kRandom);
	fireEmitter_.SetMinColor(Vector3(1.0f, 0.3f, 0.0f));
	fireEmitter_.SetMaxColor(Vector3(1.0f, 0.3f, 0.0f));
	fireEmitter_.SetMinSize(0.4f);
	fireEmitter_.SetMaxSize(0.6f);
	fireEmitter_.SetMinVelocity(Vector3(-1.0f, -1.0f, 1.0f));
	fireEmitter_.SetMaxVelocity(Vector3(1.0f, 1.0f, 1.0f));
	fireEmitter_.SetMinLifeTime(0.4f);
	fireEmitter_.SetMaxLifeTime(0.4f);

}

void Explosion::Update() {

}

void Explosion::Emit() {
	fireEmitter_.Emit();
}
