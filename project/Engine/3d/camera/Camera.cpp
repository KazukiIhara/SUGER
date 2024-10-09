// This
#include "Camera.h"

// C++
#include <cassert>

// ImGui
#include "externals/imgui/imgui.h"

void cCamera::Initialize(WorldTransform* transform) {
	assert(transform);

	transform_ = transform;
	worldMatrix_ = MakeAffineMatrix(transform_->scale, transform_->rotate, transform_->translate);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(fovY_,aspectRaito_, 0.1f, 100.0f);
	viewProjectionMatrix_ = viewMatrix * projectionMatrix;
	worldPos_ = ExtractionWorldPos(worldMatrix_);
}

void cCamera::Update() {
	worldMatrix_ = MakeAffineMatrix(transform_->scale, transform_->rotate, transform_->translate);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(fovY_, aspectRaito_, nearClipRange_, farClipRange_);
	viewProjectionMatrix_ = viewMatrix * projectionMatrix;
	worldPos_ = ExtractionWorldPos(worldMatrix_);
}
