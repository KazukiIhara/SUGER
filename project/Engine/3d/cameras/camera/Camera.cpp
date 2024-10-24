// This
#include "Camera.h"

// C++
#include <cassert>

// ImGui
#include "externals/imgui/imgui.h"

// MyHedder
#include "framework/SUGER.h"

void Camera::Initialize() {

	transform_.Initialize();
	transform_.rotate_ = kDefaultCameraRotate_;
	transform_.translate_ = kDefaultCameraTranslate_;

	worldMatrix_ = MakeAffineMatrix(transform_.scale_, transform_.rotate_, transform_.translate_);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(fovY_, aspectRaito_, nearClipRange_, farClipRange_);
	viewProjectionMatrix_ = viewMatrix * projectionMatrix;
	worldPos_ = ExtractionWorldPos(worldMatrix_);

	CreateCameraResource();
	MapCameraData();
}

void Camera::Update() {
	worldMatrix_ = MakeAffineMatrix(transform_.scale_, transform_.rotate_, transform_.translate_);
	Matrix4x4 viewMatrix = Inverse(worldMatrix_);
	Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(fovY_, aspectRaito_, nearClipRange_, farClipRange_);
	viewProjectionMatrix_ = viewMatrix * projectionMatrix;
	worldPos_ = ExtractionWorldPos(worldMatrix_);

	UpdateCameraData();
}

void Camera::CreateCameraResource() {
	cameraResource_ = SUGER::CreateBufferResource(sizeof(CameraForGPU));
}

void Camera::MapCameraData() {
	// データを書き込む
	cameraData_ = nullptr;
	// 書き込むためのアドレスを取得
	cameraResource_->Map(0, nullptr, reinterpret_cast<void**>(&cameraData_));

	// カメラ
	cameraData_->worldPosition.x = worldPos_.x;
	cameraData_->worldPosition.y = worldPos_.y;
	cameraData_->worldPosition.z = worldPos_.z;
}

void Camera::UpdateCameraData() {
	cameraData_->worldPosition.x = worldPos_.x;
	cameraData_->worldPosition.y = worldPos_.y;
	cameraData_->worldPosition.z = worldPos_.z;
}

void Camera::TransferCamera() {
	// 定数バッファを転送
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(3, cameraResource_->GetGPUVirtualAddress());
}

Vector3 Camera::GetTranslate() const {
	return transform_.translate_;
}

Vector3 Camera::GetRotate() const {
	return transform_.rotate_;
}

void Camera::SetTranslate(const Vector3& translate) {
	this->transform_.translate_ = translate;
}

void Camera::SetRotate(const Vector3& rotate) {
	this->transform_.rotate_ = rotate;
}

