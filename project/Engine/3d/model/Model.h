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
	void DrawPlaneParticle(const uint32_t& instanceCount, const std::string& textureFileName);
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
	void SetUVTransform(const std::vector<UVTransform>& uvTransforms) {
		uvTransforms_ = uvTransforms;
	}

	// マテリアルのセット
	void SetMaterials(const std::vector<Material3D>& materials) {
		materials_ = materials;
	}
	// マテリアルのゲッター
	std::vector<Material3D> GetMaterials() {
		return materials_;
	}

	// UVTransformのゲッター
	std::vector<UVTransform> GetUVTransforms() {
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
#pragma region Index
	// インデックスリソースの作成
	void CreateIndexResource();
	// インデックスバッファビューの作成
	void CreateIndexBufferView();
	// インデックスデータの書き込み
	void MapIndexData();
#pragma endregion


#pragma region Material
	/*マテリアルリソースの作成*/
	void CreateMaterialResource();
	/*マテリアルデータの書き込み*/
	void MapMaterialData();
#pragma endregion

private: // メンバ変数
#pragma region モデル
	// モデルデータ
	ModelData modelData;
#pragma endregion

#pragma region 頂点
	/*頂点リソース*/
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> vertexResources_;
	// UVあり頂点データ
	std::vector<VertexData3D*> vertexData_;
	// UVなし頂点データ
	std::vector<VertexData3DUnUV*> vertexDataUnUV_;
	/*VBV*/
	std::vector<D3D12_VERTEX_BUFFER_VIEW> vertexBufferViews_;
#pragma endregion

#pragma region インデックス
	/*インデックスリソース*/
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> indexResources_;
	/*インデックスデータ*/
	std::vector<uint32_t*> indexData_;
	/*インデックスバッファビュー*/
	std::vector<D3D12_INDEX_BUFFER_VIEW> indexBufferViews_{};
#pragma endregion

#pragma region マテリアル
	/*マテリアルリソース*/
	std::vector<Microsoft::WRL::ComPtr<ID3D12Resource>> materialResources_;
	/*マテリアルデータ*/
	std::vector<Material3D*> materialData_;
	// マテリアル
	std::vector<Material3D> materials_;
	/*uvTransform*/
	std::vector<UVTransform> uvTransforms_;
#pragma endregion

	/*球の分割数*/
	const uint32_t kSubdivision = 16;
	/*球の頂点定数*/
	const uint32_t sphereVertexNum = kSubdivision * kSubdivision * 6;

	// 板ポリの頂点数
	const uint32_t kPlaneVertexNum_ = 6;

};