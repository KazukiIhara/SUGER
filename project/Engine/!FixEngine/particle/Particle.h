#pragma once

// C++
#include <list>

#include "directX/includes/ComPtr.h"
#include "structs/ParticleStruct.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"

class Camera;
class Model;

class Particle {
public:
	Particle() = default;
	~Particle() = default;

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw();

private:
	// instancingリソース作成
	void CreateInstancingResource();
	// instancingリソース書き込み
	void MapInstancingData();

	// マテリアルリソースの作成
	void CreateMaterialResource();
	// マテリアルデータの書き込み
	void MapMaterialData();
private:
	// パーティクルの最大数
	static const uint32_t kNumMaxInstance = 100;
	// パーティクル
	std::list<ParticleData> particles_;

	// 板ポリ描画時のテクスチャファイル名
	std::string textureFileName_;

	// instancing描画用のリソース
	ComPtr<ID3D12Resource> instancingResource_ = nullptr;
	// instancing描画用のデータ
	ParticleForGPU* instancingData_ = nullptr;

	// マテリアルリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> materialResource_;
	// マテリアルデータ
	Material3D* materialData_;
	// マテリアル
	Material3D material_;

	// instance描画する際に使う変数
	uint32_t instanceCount_ = kNumMaxInstance;
	// SrvIndex
	uint32_t srvIndex_ = 0;

	// 有効フラグ
	bool isActive_ = true;

	// デルタタイムを設定。ひとまず60fps固定
	const float kDeltaTime = 1.0f / 60.0f;

};