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

class GraphicsPipelineManager {
public: // 公開メンバ変数
	GraphicsPipelineManager() = default;
	~GraphicsPipelineManager() = default;

	// 初期化
	void Initialize(DirectXManager* directXManager);

	// ルートシグネイチャのゲッター
	ID3D12RootSignature* GetRootSignature(PipelineState pipelineState) {
		return rootSignature_[pipelineState].Get();
	}

	// パイプラインステイトのゲッター
	ID3D12PipelineState* GetPipelineState(PipelineState pipelineState, BlendMode blendMode);

private:
	void SetDirectXCommon(DirectXManager* directX);
#pragma region Common
	// BlendStateの設定
	D3D12_BLEND_DESC BlendStateSetting(uint32_t blendModeNum);
#pragma endregion

#pragma region Shader
	// Dxコンパイラの初期化
	void InitializeDxCompiler();
	// シェーダーのコンパイルをまとめる関数
	void CompileShaders();

	// シェーダーをコンパイルする関数
	Microsoft::WRL::ComPtr<ID3DBlob> CompileShader(
		//CompileするShaderファイルへのパス
		const std::wstring& filePath,
		//Compileに使用するProfile
		const wchar_t* profile,
		//初期化で生成したものを3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler);
#pragma endregion

#pragma region Object2D
	// ルートシグネイチャを作成する関数
	void CreateObject2DRootSignature();
	// パイプラインを生成する関数
	void CreateObject2DGrapchicsPipelineStateObject();
	// DepthStencilStateの設定
	D3D12_DEPTH_STENCIL_DESC Object2DDepthStecilDescSetting();
	// InputLayoutの設定
	D3D12_INPUT_LAYOUT_DESC Object2DInputLayoutSetting();
	// RasterizerStateの設定
	D3D12_RASTERIZER_DESC Object2DRasterizerStateSetting();
	// シェーダーたちをコンパイルする関数
	void CompileObject2DShaders();
#pragma endregion

private: // 静的メンバ変数
	// ブレンドモードの数
	static const uint32_t kBlendModeNum = 6;
	// パイプラインの種類の数
	static const uint32_t kPipelineStateNum = 1;

private: // メンバ変数

	// ルートシグネイチャ
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature_[kPipelineStateNum];
	// グラフィックスパイプライン
	Microsoft::WRL::ComPtr<ID3D12PipelineState> graphicsPipelineState_[kPipelineStateNum][kBlendModeNum];

	// シグネイチャの塊
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	// シェーダー
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

#pragma region Object2d
	// Object2D用頂点シェーダー
	Microsoft::WRL::ComPtr<ID3DBlob> object2DVertexShaderBlob_;
	// Object2D用ピクセルシェーダー
	Microsoft::WRL::ComPtr<ID3DBlob> object2DPixelShaderBlob_;
#pragma endregion

private: // インスタンスを受け取るポインタ
	// DirectX
	DirectXManager* directX_ = nullptr;
};
