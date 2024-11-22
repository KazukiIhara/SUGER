#include "FixParticleManager.h"

#include "manager/model/ModelManager.h"
#include "manager/texture/TextureManager.h"
#include "3d/cameras/camera/Camera.h"

void FixParticleManager::Initialize(ModelManager* modelManager, TextureManager* textureManager) {
	// モデルマネージャのインスタンスをセット
	SetModelManager(modelManager);
	// テクスチャマネージャのセット
	SetTextureManager(textureManager);
	// コンテナをクリア
	ClearContainer();
}

void FixParticleManager::Update() {
	for (auto& pair : particles_) {
		if (pair.second && pair.second->GetIsActive()) {  // unique_ptr、有効フラグが有効か確認
			// 全オブジェクトを更新
			pair.second->Update();
		}
	}
}

void FixParticleManager::Draw() {
	for (auto& pair : particles_) {
		if (pair.second && pair.second->GetIsActive()) {  // unique_ptr、有効フラグが有効か確認
			// 全オブジェクトを更新
			pair.second->Draw();
		}
	}
}

void FixParticleManager::Finalize() {
	// コンテナをクリア
	ClearContainer();
}

void FixParticleManager::ClearContainer() {
	particles_.clear();
}

void FixParticleManager::CreatePlaneParticle(const std::string& name, const std::string& filePath) {
	// テクスチャを読み込み
	textureManager_->Load(filePath);
	// 新規パーティクル作成、初期化
	std::unique_ptr<Particle> newParticle = std::make_unique<Particle>();
	newParticle->Initialize(modelManager_->Find("Plane"), camera_, filePath);
	// 板ポリタイプ
	newParticle->SetType(kPlane);
	// 生成したパーティクルをmapコンテナに格納
	particles_.insert(std::make_pair(name, std::move(newParticle)));
}

void FixParticleManager::CreateModelParticle(const std::string& name, const std::string& filePath) {
	// モデルを読み込み
	modelManager_->Load(filePath);
	// 新規パーティクル作成、初期化
	std::unique_ptr<Particle> newParticle = std::make_unique<Particle>();
	newParticle->Initialize(modelManager_->Find(filePath), camera_);
	// 板ポリタイプ
	newParticle->SetType(kModel);
	// 生成したパーティクルをmapコンテナに格納
	particles_.insert(std::make_pair(name, std::move(newParticle)));
}

Particle* FixParticleManager::Find(const std::string& name) {
	// 作成済みパーティクルを検索
	if (particles_.contains(name)) {
		// オブジェクトを戻り値としてreturn
		return particles_.at(name).get();
	}
	// ファイル名一致なし
	return nullptr;
}

void FixParticleManager::SetModelManager(ModelManager* modelManager) {
	assert(modelManager);
	modelManager_ = modelManager;
}

void FixParticleManager::SetTextureManager(TextureManager* textureManager) {
	assert(textureManager);
	textureManager_ = textureManager;
}

void FixParticleManager::SetSceneCamera(Camera* camera) {
	assert(camera);
	camera_ = camera;
	for (auto& pair : particles_) {
		if (pair.second) {  // unique_ptrが有効か確認
			// カメラをセット
			pair.second->SetCamera(camera_);
		}
	}
}
