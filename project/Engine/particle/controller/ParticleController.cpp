#include "ParticleController.h"

#include <cassert>

#include "particle/3d/Particle3d.h"

void ParticleController::Initialize(Particle3D* particle3d) {
#ifdef _DEBUG
	// nullptrだった場合assert
	assert(particle3d);
#endif // DEBUG
	// パーティクルをセット
	SetParticle(particle3d);
}

void ParticleController::SetIsActive(const bool& isActive) {
	particle3d_->SetIsActive(isActive);
}

void ParticleController::SetParticle(Particle3D* particle3d) {
	particle3d_ = particle3d;
}
