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
#include "enum/ParticleEnum.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"
#include "worldTransform/WorldTransform.h"

class Camera;
class Model;

class RandomParticle {
public:
	void Initialize(Model* model, Camera* camera, const std::string& textureFileName, const EulerTransform3D& transform);
	void Update();
	void Draw(BlendMode blendMode = kBlendModeAdd);

	// カメラのセット
	void SetCamera(Camera* camera);
	// タイプのセット
	void SetType(ParticleType type);

	// 回転量のセット
	void SetRotate(const Vector3& rotate);
	// 移動量のセット
	void SetTranslate(const Vector3& translate);

	// 発生数のセット
	void SetCount(const uint32_t& count);

	// 有効フラグのセッター
	void SetIsActive(const bool& isActive);

	// 有効フラグのゲッター
	const bool& GetIsActive();

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

	// パーティクルのタイプ
	ParticleType type_;

	// Emitter
	Emitter emitter_{};

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

	// instance描画する際に使う変数
	uint32_t instanceCount_ = kNumMaxInstance;
	// SrvIndex
	uint32_t srvIndex_ = 0;

	// 板ポリ描画時のテクスチャファイル名
	std::string textureFileName_;

	// 有効フラグ
	bool isActive_ = true;

private:
	// モデルを受け取る箱
	Model* model_ = nullptr;

	// カメラを受け取る箱
	Camera* camera_ = nullptr;

};