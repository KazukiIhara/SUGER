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

class Camera;
class Model;

class Particle3D {
public:
	void Initialize(Model* model, Camera* camera);
	void Update();
	void Draw(BlendMode blendMode = kBlendModeAdd);

	// カメラのセット
	void SetCamera(Camera* camera);
private:
	// モデルのセット
	void SetModel(Model* model);

	// instancingリソース作成
	void CreateInstancingResource();
	void MapInstancingData();

	// Particleの生成
	ParticleData MakeNewParticle(std::mt19937& randomEngine, const Vector3& translate);

private:/*メンバ変数*/

	// パーティクルの最大数
	static const uint32_t kNumMaxInstance = 100;

	// モデルを受け取る箱
	Model* model_ = nullptr;

	// カメラを受け取る箱
	Camera* camera_ = nullptr;

	// instancing描画用のリソース
	ComPtr<ID3D12Resource> instancingResource_ = nullptr;
	// instancing描画用のデータ
	ParticleForGPU* instancingData_ = nullptr;

	// パーティクル
	std::list<ParticleData> particles_;
	// デルタタイムを設定。ひとまず60fps固定
	const float kDeltaTime = 1.0f / 60.0f;

	// パーティクルの発生関数
	std::list<ParticleData> Emit(const Emitter& emitter, std::mt19937& randomEngine);
	// Emitter
	Emitter emitter_{
	.count = 10,
	.frequency = 0.5f,		// 0.5秒ごとに発生
	.frequencyTime = 0.0f,	// 発生頻度用の時刻、0で初期化
	};

	// instance描画する際に使う変数
	uint32_t instanceCount_ = kNumMaxInstance;
	// SrvIndex
	uint32_t srvIndex_ = 0;
};