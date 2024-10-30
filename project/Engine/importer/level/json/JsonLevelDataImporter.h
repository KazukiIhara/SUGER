#pragma once

class JsonLevelData;
class RailCamera;

class JsonLevelDataImporter {
public:
	JsonLevelDataImporter() = default;
	~JsonLevelDataImporter() = default;

	// LevelDataをシーンにインポート
	void Import(JsonLevelData* jsonLevelData);

	// railDataをシーンにインポート
	void ImportRailControllPoint(JsonLevelData* jsonRailData, RailCamera* railCamera);

private:

};