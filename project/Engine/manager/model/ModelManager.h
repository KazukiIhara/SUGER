#pragma once

// C++
#include <map>
#include <string>
#include <memory>

// MyHedder
#include "3d/model/Model.h"

class ModelManager {
public:
	// 初期化
	void Initialize();
	// モデル読み込み
	void Load(const std::string& filePath);
	// 球体作成
	void CreateSphere(const std::string& textureFilePath, const std::string& directoryPath = "Resources");
	// モデルの検索
	Model* Find(const std::string& filePath);
	// 終了
	void Finalize();

private: // メンバ変数
	// モデルデータコンテナ
	std::map<std::string, std::unique_ptr<Model>> models_;
};

