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
	void ImportLevelwithRailControllPoint(JsonLevelData* jsonRailData, RailCamera* railCamera);

private:

};