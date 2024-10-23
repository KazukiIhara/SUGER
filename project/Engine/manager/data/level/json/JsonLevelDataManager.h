#pragma once

// C++
#include <map>
#include <string>
#include <memory>

// MyHedder
#include "data/level/json/JsonLevelData.h"

class JsonLevelDataManager {
public:
	JsonLevelDataManager() = default;
	~JsonLevelDataManager() = default;

	// 初期化
	void Initialize();
	// 終了
	void Finalize();

	// レベルデータのロード
	void Load(const std::string& fileName, const std::string& directoryPath = "resoueces/datas/levels/");

private:
	// レベルデータコンテナ
	std::map<std::string, std::unique_ptr<JsonLevelData>> levelDatas_;

};
