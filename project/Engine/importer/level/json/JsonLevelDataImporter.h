#pragma once

#include <list>
#include <memory>

class JsonLevelData;
class RailCamera;

class JsonLevelDataImporter {
public:
	JsonLevelDataImporter() = default;
	~JsonLevelDataImporter() = default;

	// LevelDataをシーンにインポート
	void Import(JsonLevelData* jsonLevelData);

private:

};