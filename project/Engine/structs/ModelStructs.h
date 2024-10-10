#pragma once
//  C++
#include <string>
#include <vector>

// MyHedder
#include "Structs/ObjectStructs.h"

// マテリアルデータ
struct sMaterialData {
	std::string textureFilePath;
	Vector4 color;
	bool haveUV_;
};

// メッシュデータ
struct sMeshData {
	std::vector<sVertexData3D> vertices;
	std::vector<sVertexData3DUnUV> verticesUnUV;
	sMaterialData material;
};

// モデルデータ
struct sModelData {
	std::vector<sMeshData> meshes;
};