#include "PunctualLight.h"

void cPunctualLight::Initialize() {
	// リソース作成
	CreatePunctualLightResource();
	CreateCameraResource();
	// データ書き込み
	MapPunctualLightData();
	MapCameraData();
}

void cPunctualLight::Update() {
	UpdateDirectionalLight();
	UpdatePointLight();
	UpdateSpotLight();

	UpdateCamera();
}

void cPunctualLight::TransferLight() {
}

void cPunctualLight::SetPunctualLightSetting(const PunctualLightData& punctualLightSetting) {
}

void cPunctualLight::SetCameraPosition(const Vector3& cameraPosition) {
}

void cPunctualLight::CreatePunctualLightResource() {
}

void cPunctualLight::MapPunctualLightData() {
}

void cPunctualLight::CreateCameraResource() {
}

void cPunctualLight::MapCameraData() {
}

void cPunctualLight::UpdateDirectionalLight() {
	punctualLightData_->directionalLight.color = punctualLight.directionalLight.color;
	punctualLightData_->directionalLight.direction = punctualLight.directionalLight.direction;
	punctualLightData_->directionalLight.intensity = punctualLight.directionalLight.intensity;
}

void cPunctualLight::UpdatePointLight() {
	punctualLightData_->pointLight.color = punctualLight.pointLight.color;
	punctualLightData_->pointLight.decay = punctualLight.pointLight.decay;
	punctualLightData_->pointLight.intensity = punctualLight.pointLight.intensity;
	punctualLightData_->pointLight.position = punctualLight.pointLight.position;
	punctualLightData_->pointLight.radius = punctualLight.pointLight.radius;
}

void cPunctualLight::UpdateSpotLight() {
	punctualLightData_->spotLight.color = punctualLight.spotLight.color;
	punctualLightData_->spotLight.cosAngle = punctualLight.spotLight.cosAngle;
	punctualLightData_->spotLight.cosFalloffStart = punctualLight.spotLight.cosFalloffStart;
	punctualLightData_->spotLight.decay = punctualLight.spotLight.decay;
	punctualLightData_->spotLight.direction = punctualLight.spotLight.direction;
	punctualLightData_->spotLight.distance = punctualLight.spotLight.distance;
	punctualLightData_->spotLight.intensity = punctualLight.spotLight.intensity;
	punctualLightData_->spotLight.position = punctualLight.spotLight.position;
}

void cPunctualLight::UpdateCamera() {
 	cameraData_->worldPosition.x = camera.worldPosition.x;
	cameraData_->worldPosition.y = camera.worldPosition.y;
	cameraData_->worldPosition.z = camera.worldPosition.z;
}
