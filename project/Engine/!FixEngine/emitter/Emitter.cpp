#include "Emitter.h"
#include <cassert>

void Emitter::Emit() {

}

void Emitter::SetParticle(Particle* particle) {
	// パーティクルがなければassert
	assert(particle);
	particle_ = particle;
}
