#pragma once

#include <string>
#include <map>
#include <memory>

#include "3d/object/Object3d.h"

class JsonLevelData {
public:
	JsonLevelData() = default;
	~JsonLevelData() = default;

	// データの読み込み
	void Load(const std::string& fullPath);

private:
	// このレベルに存在するobject3dのデータコンテナ
	std::map<std::string, std::unique_ptr<Object3D>> objects_;

};