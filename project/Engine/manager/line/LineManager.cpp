#include "LineManager.h"

void LineManager::Initialize() {
	// コンテナをクリア
	ClearContainer();
}

void LineManager::Update() {
	for (auto& pair : lines_) {
		if (pair.second) {  // unique_ptr、有効フラグが有効か確認
			// 全オブジェクトを更新
			pair.second->Update();
		}
	}
}

void LineManager::Draw() {
	for (auto& pair : lines_) {
		if (pair.second) {  // unique_ptr、有効フラグが有効か確認
			// 全オブジェクトを更新
			pair.second->Draw();
		}
	}
}

void LineManager::Finalize() {
	// コンテナをクリア
	ClearContainer();
}

void LineManager::ClearContainer() {
	lines_.clear();
}

void LineManager::CreateLine(const std::string& name) {
	// 新規ライン作成
	std::unique_ptr<Line> newLine = std::make_unique<Line>();
	newLine->Initialize(camera_);
	// 生成したラインをコンテナに追加
	lines_.insert(std::make_pair(name, std::move(newLine)));
}

Line* LineManager::Find(const std::string& name) {
	// 作成済みラインを検索
	if (lines_.contains(name)) {
		// ラインを戻り値としてreturn
		return lines_.at(name).get();
	}
	// ファイル名一致なし
	return nullptr;
}

void LineManager::SetSceneCamera(Camera* camera) {
	// マネージャにカメラをセット
	camera_ = camera;
	// 既に存在するオブジェクトにもセット
	for (auto& pair : lines_) {
		// unique_ptrが有効か確認
		if (pair.second) {
			// カメラをセット
			pair.second->SetCamera(camera_);
		}
	}
}
