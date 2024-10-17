#pragma once

//  C++
#include <string>
#include <vector>
#include <wrl.h>

// DirectX
#include <d3d12.h>

// MyHedder
#include "structs/ObjectStructs.h"
#include "structs/ModelStructs.h"

// 3Dモデル
class Model {
public: // メンバ関数
	// 初期化
	void Initialize(const std::string& filename);
	// 更新
	void Update();
	// 描画
	void Draw();
	// パーティクルの場合の描画
	void DrawParticle(const uint32_t& instanceCount);
	// モデルの読み込み
	void LoadModel(const std::string& filename, const std::string& directoryPath = "resources/models");

	// 球体の頂点作成
	void GenerateSphere(const std::string& textureFilePath);

	// 球体作成
	void CreateSphere(const std::string& textureFilePath);

	// 板ポリの頂点作成
	void GeneratePlane(const std::string& textureFilePath);

	// 板ポリ作成
	void CreatePlane(const std::string& textureFilePath);

	// UVTransformのセット
	void SetUVTransform(const std::vector<sUVTransform>& uvTransforms) {
		uvTransforms_ = uvTransforms;
	}

	// マテリアルのセット
	void SetMaterials(const std::vector<sMaterial3D>& materials) {
		materials_ = materials;
	}
	// マテリアルのゲッター
	std::vector<sMaterial3D> GetMaterials() {
		return materials_;
	}

	// UVTransformのゲッター
	std::vector<sUVTransform> GetUVTransforms() {
		return uvTransforms_;
	}

private: // メンバ関数
#pragma region Vertex
	// 頂点リソースの作成
	void CreateVertexResource();
	// 頂点バッファービューの作成
	void CreateVertexBufferView();
	// 頂点データの書き込み
	void MapVertexData();
#pragma endregion

#pragma region Material
	/*マテリアルリソースの作成*/
	void CreateMaterialResource();
	/*マテリアルデータの書き込み*/
	void MapMaterialData();
#pragma endregion

#pragma region Instancing
	// Instancingリソースを作る
	void CreateInstancingResource();
	// Instancingデータを書き込む
	void MapInstancingData();
#pragma endregion

private: // メンバ変数
#pragma region モデル
	// モデルデータ
	sModelData modelData;
#pragma endregion

#pragma region 頂点
	/*頂点リソース*/
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> vertexResources_;
	// UVあり頂点データ
	std::vector<sVertexData3D*> vertexData_;
	// UVなし頂点データ
	std::vector<sVertexData3DUnUV*> vertexDataUnUV_;
	/*VBV*/
	std::vector<D3D12_VERTEX_BUFFER_VIEW> vertexBufferViews_;
#pragma endregion

#pragma region マテリアル
	/*マテリアルリソース*/
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> materialResources_;
	/*マテリアルデータ*/
	std::vector<sMaterial3D*> materialData_;
	// マテリアル
	std::vector<sMaterial3D> materials_;
	/*uvTransform*/
	std::vector<sUVTransform> uvTransforms_;
#pragma endregion

	/*球の分割数*/
	const uint32_t kSubdivision = 16;
	/*球の頂点定数*/
	const uint32_t sphereVertexNum = kSubdivision * kSubdivision * 6;

};