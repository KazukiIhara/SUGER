#pragma once
//  C++
#include <string>
#include <vector>

// MyHedder
#include "Structs/ObjectStructs.h"

// マテリアルデータ
struct MaterialData {
	std::string textureFilePath;
	Vector4 color;
	bool haveUV_;
};

// メッシュデータ
struct MeshData {
	std::vector<VertexData3D> vertices;
	std::vector<uint32_t> indices;
	std::vector<VertexData3DUnUV> verticesUnUV;
	MaterialData material;
};

// モデルデータ
struct ModelData {
	std::vector<MeshData> meshes;
};