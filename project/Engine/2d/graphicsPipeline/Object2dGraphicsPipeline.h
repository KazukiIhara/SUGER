#pragma once

// C++
#include <string>

// DirectX
#include <d3d12.h>
#include <dxcapi.h>

// MyHedder
#include "directX/includes/ComPtr.h"
#include "enum/GraphicsPipelineEnum.h"

class DirectXManager;

class Object2DGraphicsPipeline {
public:
	Object2DGraphicsPipeline() = default;
	~Object2DGraphicsPipeline() = default;

	void Initialize(DirectXManager* directXManager);

	// ルートシグネイチャのゲッター
	ID3D12RootSignature* GetRootSignature() {
		return rootSignature_.Get();
	}

	// パイプラインステイトのゲッター
	ID3D12PipelineState* GetPipelineState(BlendMode blendMode);

private:
	void SetDirectXCommon(DirectXManager* directX);
	void CreateRootSignature();
	void CompileShaders();
	void CreateGraphicsPipelineObject();

	// シェーダーコンパイラの初期化
	void InitializeDxCompiler();

	// シェーダーをコンパイル
	ComPtr<ID3DBlob> CompileShader(
		//CompileするShaderファイルへのパス
		const std::wstring& filePath,
		//Compileに使用するProfile
		const wchar_t* profile,
		//初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);


	// BlendStateの設定
	D3D12_BLEND_DESC BlendStateSetting(uint32_t blendModeNum);
	// DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC DepthStecilDescSetting();
	// InputLayoutの設定
	D3D12_INPUT_LAYOUT_DESC InputLayoutSetting();
	// RasterizerStateの設定
	D3D12_RASTERIZER_DESC RasterizerStateSetting();

private: // 静的メンバ変数
	// ブレンドモードの数
	static const uint32_t kBlendModeNum = 6;

private:
	// ルートシグネイチャ
	ComPtr<ID3D12RootSignature> rootSignature_;
	// グラフィックスパイプライン
	ComPtr<ID3D12PipelineState> graphicsPipelineState_[kBlendModeNum];

	// 頂点シェーダー
	ComPtr<ID3DBlob> vertexShaderBlob_;
	// ピクセルシェーダー
	ComPtr<ID3DBlob> pixelShaderBlob_;

	// シェーダー
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

private: // インスタンスを受け取るポインタ
	// DirectX
	DirectXManager* directX_ = nullptr;
};
