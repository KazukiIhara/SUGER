#include "BaseScene.h"

#include "framework/SUGER.h"

void BaseScene::Initialize() {
	// カメラ作成
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	// カメラの初期位置を設定
	camera_->SetTranslate(kDefaultCameraTranslate_);

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
