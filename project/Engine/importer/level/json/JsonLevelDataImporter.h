#pragma once

class JsonLevelData;
class RailCamera;
class Baroon;

class JsonLevelDataImporter {
public:
	JsonLevelDataImporter() = default;
	~JsonLevelDataImporter() = default;

	// LevelDataをシーンにインポート
	void Import(JsonLevelData* jsonLevelData);

	// railDataをシーンにインポート
	void ImportLevel(JsonLevelData* jsonRailData, RailCamera* railCamera);

private:

};