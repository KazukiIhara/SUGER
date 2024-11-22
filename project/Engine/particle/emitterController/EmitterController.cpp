#include "EmitterController.h"

#include "framework/SUGER.h"

void EmitterController::Initialize(const std::string& name) {
	emitter_ = SUGER::FindEmitter(name);
	assert(emitter_);
}

void EmitterController::Emit() {
	emitter_->Emit();
}

void EmitterController::SetScale(const Vector3& scale) {
	emitter_->SetScale(scale);
}

void EmitterController::SetScale(const float& scale) {
	emitter_->SetScale(Vector3(scale, scale, scale));
}

void EmitterController::SetRotate(const Vector3& rotate) {
	emitter_->SetRotate(rotate);
}

void EmitterController::SetTranslate(const Vector3& translate) {
	emitter_->SetTranslate(translate);
}

void EmitterController::SetParent(WorldTransform* parent) {
	emitter_->SetParent(parent);
}

void EmitterController::SetParticle(const std::string& particleName) {
	emitter_->SetParticle(particleName);
}

void EmitterController::SetCount(const uint32_t& count) {
	emitter_->SetCount(count);
}

void EmitterController::SetIsRepeat(const bool& isRepeat) {
	emitter_->SetIsRepeat(isRepeat);
}

void EmitterController::SetIsRandom(const bool& isRandom) {
	emitter_->SetIsRandom(isRandom);
}

void EmitterController::SetRandomMinPosition(const Vector3& randomMinPosition) {
	emitter_->SetRandomMinPosition(randomMinPosition);
}

void EmitterController::SetRandomMaxPosition(const Vector3& randomMaxPosition) {
	emitter_->SetRandomMaxPosition(randomMaxPosition);
}

void EmitterController::SetRandomMinVelocity(const Vector3& randomMinVelocity) {
	emitter_->SetRandomMinVelocity(randomMinVelocity);
}

void EmitterController::SetRandomMaxVelocity(const Vector3& randomMaxVelocity) {
	emitter_->SetRandomMaxVelocity(randomMaxVelocity);
}

void EmitterController::SetRandomMinColor(const Vector3& randomMinColor) {
	emitter_->SetRandomMinColor(randomMinColor);
}

void EmitterController::SetRandomMaxColor(const Vector3& randomMaxColor) {
	emitter_->SetRandomMaxColor(randomMaxColor);
}

void EmitterController::SetRandomMinLifeTime(float randomMinLifeTime) {
	emitter_->SetRandomMinLifeTime(randomMinLifeTime);
}

void EmitterController::SetRandomMaxLifeTime(float randomMaxLifeTime) {
	emitter_->SetRandomMaxLifeTime(randomMaxLifeTime);
}

const Vector3& EmitterController::GetScale() const {
	return emitter_->GetScale();
}

const Vector3& EmitterController::GetRotate() const {
	return emitter_->GetRotate();
}

const Vector3& EmitterController::GetTranslate() const {
	return emitter_->GetTranslate();
}

Vector3 EmitterController::GetWorldPosition() const {
	return emitter_->GetWorldPosition();
}

WorldTransform* EmitterController::GetWorldTransformPtr() {
	return emitter_->GetWorldTransformPtr();
}