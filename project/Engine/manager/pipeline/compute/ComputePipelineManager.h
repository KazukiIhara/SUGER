#pragma once

// C++
#include <string>
#include <memory>

// DirectX
#include <d3d12.h>
#include <dxcapi.h>

// MyHedder
#include "directX/includes/ComPtr.h"

class DirectXManager;

class ComputePipelineManager {
public:
	ComputePipelineManager() = default;
	~ComputePipelineManager() = default;

	// 初期化
	void Initialize(DirectXManager* directXManager);


private:
	// パイプラインの種類の数 
	static const uint32_t kComputePipelineStateNum = 1;

private:


};