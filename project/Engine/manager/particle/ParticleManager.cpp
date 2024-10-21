#include "ParticleManager.h"

#include "manager/model/ModelManager.h"
#include "3d/cameras/camera/Camera.h"

void ParticleManager::Initialize(ModelManager* modelManager) {
	// モデルマネージャのインスタンスをセット
	SetModelManager(modelManager);
	// コンテナをクリア
	objects_.clear();
}

void ParticleManager::Update() {
	for (auto& pair : objects_) {
		if (pair.second) {  // unique_ptrが有効か確認
			// 全オブジェクトを更新
			pair.second->Update();
		}
	}
}

void ParticleManager::Draw() {
	for (auto& pair : objects_) {
		if (pair.second) {  // unique_ptrが有効か確認
			// 全オブジェクトを更新
			pair.second->Draw();
		}
	}
}

void ParticleManager::Finalize() {
	// 配列をクリア
	objects_.clear();
}

void ParticleManager::Create(const std::string& name, const std::string& filePath) {
	// 板ポリ生成
	modelManager_->CreatePlane(filePath);
	// パーティクルエミッタの生成と初期化
	std::unique_ptr<Particle3D> newObject = std::make_unique<Particle3D>();
	newObject->Initialize(modelManager_->Find("Plane"), camera_);

	// 生成したパーティクルをmapコンテナに格納
	objects_.insert(std::make_pair(name, std::move(newObject)));
}

void ParticleManager::SetModelManager(ModelManager* modelManager) {
	modelManager_ = modelManager;
}

void ParticleManager::SetSceneCamera(Camera* camera) {
	camera_ = camera;
	for (auto& pair : objects_) {
		if (pair.second) {  // unique_ptrが有効か確認
			// カメラをセット
			pair.second->SetCamera(camera_);
		}
	}
}
