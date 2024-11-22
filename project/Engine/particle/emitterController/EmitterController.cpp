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

void EmitterController::SetIsRepeat(const bool& isRepeat) {
	emitter_->SetIsRepeat(isRepeat);
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