#include "WorldTransform.h"

void WorldTransform::Initialize() {
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = { 0.0f,0.0f,0.0f };
	translate_ = { 0.0f,0.0f,0.0f };
	worldMatrix_ = MakeIdentityMatrix4x4();
}

void WorldTransform::Update() {
	worldMatrix_ = MakeAffineMatrix(scale_, rotate_, translate_);
}