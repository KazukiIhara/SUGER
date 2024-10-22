#include "Object3DManager.h"

#include "manager/model/ModelManager.h"
#include "3d/cameras/camera/Camera.h"
#include "3d/lights/punctualLight/PunctualLight.h"

void Object3DManager::Initialize(ModelManager* modelManager) {
	// モデルマネージャのインスタンスをセット
	SetModelManager(modelManager);
	// コンテナをクリア
	objects_.clear();
}

void Object3DManager::Update() {
	for (auto& pair : objects_) {
		if (pair.second && pair.second->GetIsActive()) {  // unique_ptrが有効かつオブジェクトが有効状態
			// 全オブジェクトを更新
			pair.second->Update();
		}
	}
}

void Object3DManager::Draw() {
	for (auto& pair : objects_) {
		if (pair.second && pair.second->GetIsActive()) {  // unique_ptrが有効かつオブジェクトが有効状態
			// 全オブジェクトを描画
			pair.second->Draw();
		}
	}
}

void Object3DManager::Finalize() {
	// コンテナをクリア
	objects_.clear();
}

void Object3DManager::Create(const std::string& name, const std::string& filePath, const Transform3D& transform) {
	// オブジェクトの生成と初期化
	std::unique_ptr<Object3D> newObject = std::make_unique<Object3D>();
	newObject->Initialize();

	// 名前のセット
	newObject->SetName(name);

	// トランスフォームのセット
	newObject->SetScale(transform.scale);
	newObject->SetRotate(transform.rotate);
	newObject->SetTranslate(transform.translate);

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
	objects_.insert(std::make_pair(name, std::move(newObject)));
}

Object3D* Object3DManager::Find(const std::string& name) {
	// 作成済みオブジェクトを検索
	if (objects_.contains(name)) {
		// オブジェクトを戻り値としてreturn
		return objects_.at(name).get();
	}
	// ファイル名一致なし
	return nullptr;
}

void Object3DManager::SetRequiredObjects(Camera* camera, PunctualLight* punctualLight) {
	SetSceneCamera(camera);
	SetScenePunctualLight(punctualLight);
}

void Object3DManager::SetModelManager(ModelManager* modelManager) {
	modelManager_ = modelManager;
}

void Object3DManager::SetSceneCamera(Camera* camera) {
	// マネージャにカメラをセット
	camera_ = camera;
	// 既に存在するオブジェクトにもセット
	for (auto& pair : objects_) {
		if (pair.second) {  // unique_ptrが有効か確認
			// カメラをセット
			pair.second->SetCamera(camera_);
		}
	}
}

void Object3DManager::SetScenePunctualLight(PunctualLight* punctualLight) {
	light_ = punctualLight;
}
