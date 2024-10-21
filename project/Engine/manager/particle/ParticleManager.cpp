#include "ParticleManager.h"

#include "manager/model/ModelManager.h"
#include "manager/texture/TextureManager.h"
#include "3d/cameras/camera/Camera.h"

void ParticleManager::Initialize(ModelManager* modelManager, TextureManager* textureManager) {
	// モデルマネージャのインスタンスをセット
	SetModelManager(modelManager);
	// テクスチャマネージャのセット
	SetTextureManager(textureManager);
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

void ParticleManager::CreatePlane(const std::string& name, const std::string& filePath, const Transform3D& transform) {
	// 板ポリ生成
	textureManager_->Load(filePath);
	// パーティクルエミッタの生成と初期化
	std::unique_ptr<Particle3D> newObject = std::make_unique<Particle3D>();
	newObject->Initialize(modelManager_->Find("Plane"), camera_, filePath, transform);
	// 板ポリタイプ
	newObject->SetType(kPlane);
	// 生成したパーティクルをmapコンテナに格納
	objects_.insert(std::make_pair(name, std::move(newObject)));
}

void ParticleManager::SetModelManager(ModelManager* modelManager) {
	modelManager_ = modelManager;
}

void ParticleManager::SetTextureManager(TextureManager* textureManager) {
	textureManager_ = textureManager;
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
