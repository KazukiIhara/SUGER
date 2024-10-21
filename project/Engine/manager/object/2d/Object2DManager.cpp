#include "Object2DManager.h"

void Object2DManager::Initialize() {
	// コンテナをクリア
	objects_.clear();
}

void Object2DManager::Update() {
	for (auto& pair : objects_) {
		if (pair.second) {  // unique_ptrが有効か確認
			// 全オブジェクトを更新
			pair.second->Update();
		}
	}
}

void Object2DManager::Draw() {
	for (auto& pair : objects_) {
		if (pair.second) {  // unique_ptrが有効か確認
			// 全オブジェクトを描画
			pair.second->Draw();
		}
	}
}

void Object2DManager::Finalize() {
	// コンテナをクリア
	objects_.clear();
}

void Object2DManager::Create(const std::string& name, const std::string& filePath) {
	// オブジェクトの生成と初期化
	std::unique_ptr<Sprite> newObject = std::make_unique<Sprite>();
	newObject->Initialize(filePath);

	// 2Dオブジェクトをコンテナに格納する
	objects_.insert(std::make_pair(filePath, std::move(newObject)));
}