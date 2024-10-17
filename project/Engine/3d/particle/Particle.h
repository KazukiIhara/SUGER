#pragma once

// C++
#include <memory>
#include <random>
#include <iostream>
#include <list>
#include <algorithm>

#include "directX/includes/ComPtr.h"
#include "structs/ObjectStructs.h"
#include "structs/ModelStructs.h"
#include "structs/ParticleStruct.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"
#include "worldTransform/WorldTransform.h"
#include "3d/model/Model.h"
#include "3d/lights/punctualLight/PunctualLight.h"
#include "3d/cameras/camera/Camera.h"


class cParticleSystem {
public:
	void Initialize(Matrix4x4* viewProjection, sUVTransform* uvTransform);
	void Update(const Matrix4x4& cameraMatrix);
	void Draw(uint32_t textureHandle, BlendMode blendMode);

private:

#pragma region Instancing
	void CreateInstancingResource();
	void MapInstancingData();

#pragma endregion
#pragma region Particle
	// Particleの生成
	Particle MakeNewParticle(std::mt19937& randomEngine, const Vector3& translate);

#pragma endregion
	// instancingSrvを作る
	void CreateSRV();

private:/*メンバ変数*/

	// パーティクルの最大数
	static const uint32_t kNumMaxInstance = 100;

#pragma region モデル
	// モデルを受け取る箱
	Model* model = nullptr;

#pragma endregion

#pragma region 頂点
	/*頂点リソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource_ = nullptr;
	/*頂点データ*/
	sVertexData3D* vertexData_;
	/*VBV*/
	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_;
#pragma endregion

#pragma region インデックス
	/*インデックスリソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> indexResource_ = nullptr;
	/*インデックスバッファビュー*/
	D3D12_INDEX_BUFFER_VIEW indexBufferView_{};
	/*インデックスデータ*/
	uint32_t* indexData_;
#pragma endregion

#pragma region マテリアル
	/*マテリアルリソース*/
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_ = nullptr;
	/*マテリアルデータ*/
	sMaterial3D* materialData_ = nullptr;
	/*uvTransformを受け取る箱*/
	sUVTransform* uvTransform_;
#pragma endregion

#pragma region 変換
	/*ビュープロジェクションを受け取る箱*/
	Matrix4x4* viewProjection_;
#pragma endregion

#pragma region Instancing
	Microsoft::WRL::ComPtr<ID3D12Resource> instancingResource_ = nullptr;
	ParticleForGPU* instancingData_ = nullptr;
#pragma endregion

#pragma region Particle

	// パーティクル
	std::list<Particle> particles_;
	// デルタタイムを設定。ひとまず60fps固定
	const float kDeltaTime = 1.0f / 60.0f;

#pragma endregion
#pragma region Emitter
	// パーティクルの発生関数
	std::list<Particle> Emit(const Emitter& emitter, std::mt19937& randomEngine);
	// Emitter
	Emitter emitter_{
	.count = 3,
	.frequency = 0.5f,		// 0.5秒ごとに発生
	.frequencyTime = 0.0f,	// 発生頻度用の時刻、0で初期化
	};
#pragma endregion

	// instance描画する際に使う変数
	uint32_t instanceCount_ = kNumMaxInstance;

	// SrvIndex
	uint32_t srvIndex_ = 0;

	/// 
	/// for Debug
	/// 
	bool isUpdate = false;
	bool isUseBillboard = false;
};