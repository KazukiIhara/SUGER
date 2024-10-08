#include "WorldTransform.h"

void WorldTransform::Initialize() {
	scale = { 1.0f,1.0f,1.0f };
	rotate = { 0.0f,0.0f,0.0f };
	translate = { 0.0f,0.0f,0.0f };
	worldMatrix_ = MakeIdentityMatrix4x4();
}

void WorldTransform::Update() {
	worldMatrix_ = MakeAffineMatrix(scale, rotate, translate);
}