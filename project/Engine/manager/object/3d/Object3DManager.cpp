#include "Object3DManager.h"

#include "manager/model/ModelManager.h"
#include "3d/camera/Camera.h"
#include "3d/lights/punctualLight/PunctualLight.h"

void Object3DManager::Initialize(ModelManager* modelManager) {
	// モデルマネージャのインスタンスをセット
	SetModelManager(modelManager);
	// コンテナをクリア
	objects_.clear();
}

void Object3DManager::Update() {
	for (auto& pair : objects_) {
		if (pair.second) {  // unique_ptrが有効か確認
			// 全オブジェクトを更新
			pair.second->Update();
		}
	}
}

void Object3DManager::Draw() {
	for (auto& pair : objects_) {
		if (pair.second) {  // unique_ptrが有効か確認
			// 全オブジェクトを描画
			pair.second->Draw();
		}
	}
}

void Object3DManager::Finalize() {
	// コンテナをクリア
	objects_.clear();
}

void Object3DManager::Create(const WorldTransform& worldTransform, const std::string& name, const std::string& filePath) {
	// オブジェクトの生成と初期化
	std::unique_ptr<Object3D> newObject = std::make_unique<Object3D>();
	newObject->Initialize();

	// トランスフォームのセット
	newObject->SetScale(worldTransform.scale);
	newObject->SetRotate(worldTransform.rotate);
	newObject->SetTranslate(worldTransform.translate);

	// カメラのセット
	newObject->SetCamera(camera_);
	// ライトのセット
	newObject->SetPunctualLight(light_);

	// filePathの指定がある場合、モデル読み込み
	if (!filePath.empty()) {
		modelManager_->Load(filePath);
		newObject->SetModel(filePath);
	}

	// 3Dオブジェクトをコンテナに格納する
	objects_.insert(std::make_pair(filePath, std::move(newObject)));
}

void Object3DManager::SetRequiredObjects(Camera* camera, PunctualLight* punctualLight) {
	SetSceneCamera(camera);
	SetScenePunctualLight(punctualLight);
}

void Object3DManager::SetModelManager(ModelManager* modelManager) {
	modelManager_ = modelManager;
}

void Object3DManager::SetSceneCamera(Camera* camera) {
	camera_ = camera;
}

void Object3DManager::SetScenePunctualLight(PunctualLight* punctualLight) {
	light_ = punctualLight;
}
