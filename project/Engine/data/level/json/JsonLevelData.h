#pragma once

#include <string>
#include <map>
#include <memory>
#include <vector>

#include "3d/object/Object3d.h"

class JsonLevelData {
public:
	JsonLevelData() = default;
	~JsonLevelData() = default;

	// データの読み込み
	void Load(const std::string& fullpath);

	// 3Dオブジェクトコンテナのゲッター
	std::vector<ObjectData3D> Get3DObjects()const;

private:
	// このレベルに存在するobject3dのデータコンテナ
	std::vector<ObjectData3D> objects_;

};