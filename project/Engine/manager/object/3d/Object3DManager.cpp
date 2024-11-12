#include "Object3DManager.h"

#include "manager/model/ModelManager.h"
#include "3d/cameras/camera/Camera.h"
#include "3d/lights/punctualLight/PunctualLight.h"

void Object3DManager::Initialize(ModelManager* modelManager) {
	// モデルマネージャのインスタンスをセット
	SetModelManager(modelManager);
	// コンテナをクリア
	Clear();
}

void Object3DManager::Update() {
	// 削除フラグが立っているオブジェクトを削除
	std::erase_if(objects_, [](auto& pair) {
		return pair.second && pair.second->GetIsDelete();
		});

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
			// スキニングなし全オブジェクトを描画
			if (!pair.second->GetHaveSkinningModel()) {
				pair.second->Draw();
			}
		}
	}
}

void Object3DManager::DrawSkinning() {
	for (auto& pair : objects_) {
		if (pair.second && pair.second->GetIsActive()) {  // unique_ptrが有効かつオブジェクトが有効状態
			// スキニングあり全オブジェクトを描画
			if (pair.second->GetHaveSkinningModel()) {
				pair.second->DrawSkinning();
			}
		}
	}
}

void Object3DManager::Clear() {
	objects_.clear();
}

void Object3DManager::Finalize() {
	// コンテナをクリア
	Clear();
}

std::string Object3DManager::Create(const std::string& name, const std::string& fileName, const EulerTransform3D& transform) {
	// 重複した名前がある場合、番号を付加してユニークな名前を作成
	std::string uniqueName = name;
	int counter = 0;
	while (objects_.find(uniqueName) != objects_.end()) {
		counter++;
		uniqueName = name + "_" + std::to_string(counter);
	}

	// オブジェクトの生成と初期化
	std::unique_ptr<Object3D> newObject = std::make_unique<Object3D>();
	newObject->Initialize();

	// ユニークな名前をセット
	newObject->SetName(uniqueName);

	// トランスフォームのセット
	newObject->SetScale(transform.scale);
	newObject->SetRotate(transform.rotate);
	newObject->SetTranslate(transform.translate);

	// カメラのセット
	newObject->SetCamera(camera_);
	// ライトのセット
	newObject->SetPunctualLight(light_);

	// 値を代入した後に一回更新
	newObject->Update();

	// filePathの指定がある場合、モデル読み込み
	if (!fileName.empty()) {
		modelManager_->Load(fileName);
		newObject->SetModel(fileName);
	}

	// 3Dオブジェクトをコンテナに格納する
	objects_.insert(std::make_pair(uniqueName, std::move(newObject)));

	// オブジェクトの番号を返す
	return uniqueName;
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
