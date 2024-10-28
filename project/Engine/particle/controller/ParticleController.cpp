#include "ParticleController.h"

#include <cassert>

#include "particle/random/RandomParticle.h"

void ParticleController::Initialize(RandomParticle* particle3d) {
#ifdef _DEBUG
	// nullptrだった場合assert
	assert(particle3d);
#endif // DEBUG
	// パーティクルをセット
	SetParticle(particle3d);
}

void ParticleController::SetRotate(const Vector3& rotate) {
	particle3d_->SetRotate(rotate);
}

void ParticleController::SetTranslate(const Vector3& translate) {
	particle3d_->SetTranslate(translate);
}

void ParticleController::SetIsActive(const bool& isActive) {
	particle3d_->SetIsActive(isActive);
}

void ParticleController::SetParticle(RandomParticle* particle3d) {
	particle3d_ = particle3d;
}
