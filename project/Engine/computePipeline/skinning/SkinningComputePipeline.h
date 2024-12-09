#pragma once

// C++
#include <string>

// DirectX
#include <d3d12.h>
#include <dxcapi.h>

// ヘッダファイル
#include "directX/includes/ComPtr.h"

class DirectXManager;

class SkinningComputePipeline {
public:
	SkinningComputePipeline() = default;
	~SkinningComputePipeline() = default;

	// 初期化
	void Initialize(DirectXManager* directXManager);

	// ルートシグネチャを取得する
	ID3D12RootSignature* GetRootSignature();

	// パイプラインステートを取得する
	ID3D12PipelineState* GetPipelineState();

private:
	// DirectXのインスタンスをセット
	void SetDirectXManager(DirectXManager* directX);

	// ルートシグネチャを作成する
	void CreateRootSignature();

	// シェーダーをコンパイルする
	void CompileShaders();

	// グラフィックスパイプラインオブジェクトを作成する
	void CreatePipelineStateObject();

	// シェーダーコンパイラの初期化
	void InitializeDxCompiler();

	// シェーダーをコンパイルする
	ComPtr<ID3DBlob> CompileShader(
		// シェーダーファイルのパス
		const std::wstring& filePath,
		// コンパイルに使用するプロファイル
		const wchar_t* profile,
		// 初期化で生成したシェーダーコンパイラ関連の3つ
		IDxcUtils* dxcUtils,
		IDxcCompiler3* dxcCompiler,
		IDxcIncludeHandler* includeHandler
	);

private:
	// ルートシグネチャ
	ComPtr<ID3D12RootSignature> rootSignature_;

	// パイプラインステート
	ComPtr<ID3D12PipelineState> pipelineState_;

	// コンピュートシェーダーのバイナリデータ
	ComPtr<ID3DBlob> computeShaderBlob_;

	// シェーダーコンパイルに使用するオブジェクト
	IDxcUtils* dxcUtils = nullptr;
	IDxcCompiler3* dxcCompiler = nullptr;
	IDxcIncludeHandler* includeHandler = nullptr;

private: // ポインタでDirectXManagerのインスタンスを保持
	DirectXManager* directX_ = nullptr;
};