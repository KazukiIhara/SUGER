// This
#include "Camera.h"

// C++
#include <cassert>

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "framework/SUGER.h"

void Camera::Initialize(WorldTransform* transform) {
	assert(transform);

	transform_ = transform;
	worldMatrix_ = MakeAffineMatrix(transform_->scale, transform_->rotate, transform_->translate);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(fovY_, aspectRaito_, 0.1f, 100.0f);
	viewProjectionMatrix_ = viewMatrix * projectionMatrix;
	worldPos_ = ExtractionWorldPos(worldMatrix_);

	CreateCameraResource();
	MapCameraData();
}

void Camera::Update() {
	worldMatrix_ = MakeAffineMatrix(transform_->scale, transform_->rotate, transform_->translate);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(fovY_, aspectRaito_, nearClipRange_, farClipRange_);
	viewProjectionMatrix_ = viewMatrix * projectionMatrix;
	worldPos_ = ExtractionWorldPos(worldMatrix_);

	UpdateCamera();
}

void Camera::CreateCameraResource() {
	cameraResource_ = SUGER::CreateBufferResource(sizeof(sCameraForGPU));
}

void Camera::MapCameraData() {
	// データを書き込む
	cameraData_ = nullptr;
	// 書き込むためのアドレスを取得
	cameraResource_->Map(0, nullptr, reinterpret_cast<void**>(&cameraData_));

	// カメラ
	cameraData_->worldPosition.x = camera.worldPosition.x;
	cameraData_->worldPosition.y = camera.worldPosition.y;
	cameraData_->worldPosition.z = camera.worldPosition.z;
}

void Camera::UpdateCamera() {
	cameraData_->worldPosition.x = camera.worldPosition.x;
	cameraData_->worldPosition.y = camera.worldPosition.y;
	cameraData_->worldPosition.z = camera.worldPosition.z;
}

void Camera::TransferCamera() {
	// 定数バッファを転送
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(3, cameraResource_->GetGPUVirtualAddress());
}
