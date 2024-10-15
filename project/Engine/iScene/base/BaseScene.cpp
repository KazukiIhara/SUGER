#include "BaseScene.h"

#include "framework/SUGER.h"

void BaseScene::Initialize() {
	// カメラ作成
	cameraTransform_.Initialize();
	cameraTransform_.translate.z = -10.0f;
	camera_ = std::make_unique<Camera>();
	camera_->Initialize(&cameraTransform_);

	// ライト作成
	light_ = std::make_unique<PunctualLight>();
	light_->Initialize();

	// シーンに必要なカメラとライトのセット
	SUGER::SetRequiredObjects(camera_.get(), light_.get());
}

void BaseScene::Update() {
	camera_->Update();
	light_->Update();
}
