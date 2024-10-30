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
	// レールのコントロールポイントコンテナのゲッター
	std::vector<Vector3> GetControlPoints()const;

private:
	// このレベルに存在するobject3dのデータコンテナ
	std::vector<ObjectData3D> objects_;
	// このレベルに存在するレールのコントロールポイントのデータコンテナ
	std::vector<Vector3> controlPoints_;

};