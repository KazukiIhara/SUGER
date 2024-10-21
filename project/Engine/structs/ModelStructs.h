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
	std::vector<VertexData3D> vertices;
	std::vector<VertexData3DUnUV> verticesUnUV;
	sMaterialData material;
};

// モデルデータ
struct sModelData {
	std::vector<sMeshData> meshes;
};