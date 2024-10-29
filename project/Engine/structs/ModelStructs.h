#pragma once
//  C++
#include <string>
#include <vector>
#include <map>

// MyHedder
#include "Structs/ObjectStructs.h"


// ノード
struct Node {
	QuaternionTransform3D transform;
	Matrix4x4 localMatrix;
	std::string name;
	std::vector<Node> children;
};

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
	Node rootNode;
};

// モデルデータ
struct ModelData {
	std::vector<MeshData> meshes;
};

// Vector3のアニメーションキーフレーム
struct KeyframeVector3 {
	Vector3 value;
	float time;
};

// Quaternionのアニメーションキーフレーム
struct KeyframeQuaternion {
	Quaternion value;
	float time;
};

// Nodeアニメーション
struct NodeAnimation {
	std::vector<KeyframeVector3> translate;
	std::vector<KeyframeQuaternion> rotate;
	std::vector<KeyframeVector3> scale;
};

// アニメーション
struct Animation {
	float duration;
	std::map<std::string, NodeAnimation> nodeAnimations;
};