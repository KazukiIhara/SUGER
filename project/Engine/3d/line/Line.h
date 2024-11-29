#pragma once

// C++
#include <list>

#include "directX/includes/ComPtr.h"
#include "structs/LineStruct.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"

class Camera;

class Line {
public:
	Line() = default;
	~Line() = default;

	// 初期化
	void Initialize(Camera* camera);
	// 更新
	void Update();
	// 描画
	void Draw();

	// 描画するライン追加
	void AddLine();

	// ラインのクリア
	void ClearLines();

	// カメラのセット
	void SetCamera(Camera* camera);

	// 有効フラグのセッター
	void SetIsActive(const bool& isActive);
private:
	// instancingリソース作成
	void CreateInstancingResource();
	// instancingリソース書き込み
	void MapInstancingData();

private:
	// ラインの最大数
	static const uint32_t kNumMaxInstance = 512;
	// ライン
	std::list<LineData3D> lines_;

	// instancing描画用のリソース
	ComPtr<ID3D12Resource> instancingResource_ = nullptr;
	// instancing描画用のデータ
	LineData3D* instancingData_ = nullptr;

	// SrvIndex
	uint32_t srvIndex_ = 0;
	// カメラを受け取る箱
	Camera* camera_ = nullptr;
	// instance描画する際に使う変数
	uint32_t instanceCount_ = kNumMaxInstance;
	// 有効フラグ
	bool isActive_ = true;
};