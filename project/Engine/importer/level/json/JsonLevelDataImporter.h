#pragma once

class JsonLevelData;

class JsonLevelDataImporter {
public:
	JsonLevelDataImporter() = default;
	~JsonLevelDataImporter() = default;

	// LevelDataをシーンにインポート
	void Import(JsonLevelData* jsonLevelData);

private:

};