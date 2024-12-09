#include "SkinningComputePipeline.h"

#include <cassert>

#include "debugTools/logger/Logger.h"
#include "manager/directX/DirectXManager.h"

void SkinningComputePipeline::Initialize(DirectXManager* directXManager) {
	SetDirectXManager(directXManager);
	InitializeDxCompiler();
	CreateRootSignature();
	CompileShaders();
	CreatePipelineStateObject();
}

ID3D12RootSignature* SkinningComputePipeline::GetRootSignature() {
	return rootSignature_.Get();
}

ID3D12PipelineState* SkinningComputePipeline::GetPipelineState() {
	return pipelineState_.Get();
}

void SkinningComputePipeline::SetDirectXManager(DirectXManager* directX) {
	directX_ = directX;
}

void SkinningComputePipeline::CreateRootSignature() {
	HRESULT hr = S_FALSE;

	// Descriptor Ranges
	// SRV用
	D3D12_DESCRIPTOR_RANGE srvRanges[1] = {};
	srvRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
	srvRanges[0].NumDescriptors = 3;                 // t0, t1, t2
	srvRanges[0].BaseShaderRegister = 0;             // t0から始まる
	srvRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// UAV用
	D3D12_DESCRIPTOR_RANGE uavRanges[1] = {};
	uavRanges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
	uavRanges[0].NumDescriptors = 1;                 // u0のみ
	uavRanges[0].BaseShaderRegister = 0;             // u0から始まる
	uavRanges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

	// Root Parameters
	// 1) CBV(b0)をRoot Descriptorとして渡す
	D3D12_ROOT_PARAMETER rootParams[3] = {};

	// CBV用パラメータ (b0)
	rootParams[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_CBV;
	rootParams[0].Descriptor.ShaderRegister = 0; // b0
	rootParams[0].Descriptor.RegisterSpace = 0;
	rootParams[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	// SRV Descriptor Table用パラメータ (t0~t2)
	rootParams[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParams[1].DescriptorTable.NumDescriptorRanges = _countof(srvRanges);
	rootParams[1].DescriptorTable.pDescriptorRanges = srvRanges;
	rootParams[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	// UAV Descriptor Table用パラメータ (u0)
	rootParams[2].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
	rootParams[2].DescriptorTable.NumDescriptorRanges = _countof(uavRanges);
	rootParams[2].DescriptorTable.pDescriptorRanges = uavRanges;
	rootParams[2].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

	// Static Samplers
	D3D12_STATIC_SAMPLER_DESC staticSamplers[1] = {};
	// 特にサンプラーを使わない場合は設定しないか、デフォルト設定のサンプラーを用意する
	staticSamplers[0].Filter = D3D12_FILTER_MIN_MAG_MIP_LINEAR;
	staticSamplers[0].AddressU = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressV = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].AddressW = D3D12_TEXTURE_ADDRESS_MODE_WRAP;
	staticSamplers[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;
	staticSamplers[0].ShaderRegister = 0;
	staticSamplers[0].RegisterSpace = 0;
	staticSamplers[0].MaxLOD = D3D12_FLOAT32_MAX;

	// Root Signature Description
	D3D12_ROOT_SIGNATURE_DESC rootSigDesc = {};
	rootSigDesc.NumParameters = _countof(rootParams);
	rootSigDesc.pParameters = rootParams;
	rootSigDesc.NumStaticSamplers = _countof(staticSamplers);
	rootSigDesc.pStaticSamplers = staticSamplers;
	rootSigDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE; // Compute用であるためIA関連フラグは不要

	// シリアライズしてバイナリにする
	ID3DBlob* signatureBlob = nullptr;
	ID3DBlob* errorBlob = nullptr;

	hr = D3D12SerializeRootSignature(&rootSigDesc,
		D3D_ROOT_SIGNATURE_VERSION_1, &signatureBlob, &errorBlob);
	if (FAILED(hr)) {
		Logger::Log(reinterpret_cast<char*>(errorBlob->GetBufferPointer()));
		assert(false);
	}
	// バイナリをもとに生成
	rootSignature_ = nullptr;
	hr = directX_->GetDevice()->CreateRootSignature(0, signatureBlob->GetBufferPointer(),
		signatureBlob->GetBufferSize(), IID_PPV_ARGS(&rootSignature_));
	assert(SUCCEEDED(hr));

}

void SkinningComputePipeline::CompileShaders() {
	computeShaderBlob_ = nullptr;
	computeShaderBlob_ = CompileShader(L"resources/shaders/skinning/skinning.CS.hlsl",
		L"cs_6_0", dxcUtils, dxcCompiler, includeHandler);
	assert(computeShaderBlob_ != nullptr);
}

void SkinningComputePipeline::CreatePipelineStateObject() {
	HRESULT hr;

	assert(rootSignature_);
	assert(computeShaderBlob_);

	D3D12_COMPUTE_PIPELINE_STATE_DESC computePipelineStateDesc{};
	computePipelineStateDesc.CS = {
		.pShaderBytecode = computeShaderBlob_->GetBufferPointer(),
		.BytecodeLength = computeShaderBlob_->GetBufferSize(),
	};
	computePipelineStateDesc.pRootSignature = rootSignature_.Get();
	pipelineState_ = nullptr;
	hr = directX_->GetDevice()->CreateComputePipelineState(&computePipelineStateDesc, IID_PPV_ARGS(&pipelineState_));
	assert(SUCCEEDED(hr));
}

void SkinningComputePipeline::InitializeDxCompiler() {
	HRESULT hr = S_FALSE;
	// dxCompilerを初期化
	hr = DxcCreateInstance(CLSID_DxcUtils, IID_PPV_ARGS(&dxcUtils));
	assert(SUCCEEDED(hr));
	hr = DxcCreateInstance(CLSID_DxcCompiler, IID_PPV_ARGS(&dxcCompiler));
	assert(SUCCEEDED(hr));
	hr = dxcUtils->CreateDefaultIncludeHandler(&includeHandler);
	assert(SUCCEEDED(hr));
}

ComPtr<ID3DBlob> SkinningComputePipeline::CompileShader(const std::wstring& filePath, const wchar_t* profile, IDxcUtils* dxcUtils, IDxcCompiler3* dxcCompiler, IDxcIncludeHandler* includeHandler) {
	// これからシェーダーをコンパイルする旨をログに出す
	Logger::Log(Logger::ConvertString(std::format(L"Begin CompileShader, path:{}, profile:{}\n", filePath, profile)));
	// hlslファイルを読む
	Microsoft::WRL::ComPtr<IDxcBlobEncoding> shaderSource = nullptr;
	HRESULT hr = dxcUtils->LoadFile(filePath.c_str(), nullptr, &shaderSource);
	// 読めなかったら止める
	assert(SUCCEEDED(hr));
	// 読み込んだファイルの内容を設定する
	DxcBuffer shaderSourceBuffer{};
	shaderSourceBuffer.Ptr = shaderSource->GetBufferPointer();
	shaderSourceBuffer.Size = shaderSource->GetBufferSize();
	shaderSourceBuffer.Encoding = DXC_CP_UTF8;//UTF8の文字コードであることを通知

	LPCWSTR arguments[] = {
		filePath.c_str(),// コンパイル対象のhlslファイル名
		L"-E",L"main",// エントリーポイントの指定。基本的にmain以外にはしない
		L"-T",profile,// ShaderProfileの設定
		L"-Zi",L"-Qembed_debug",// デバッグ用の情報を埋め込む
		L"-Od",// 最適化を外しておく
		L"-Zpr",// メモリレイアウトは行優先
	};
	// 実際にシェーダーをコンパイルする
	Microsoft::WRL::ComPtr<IDxcResult> shaderResult = nullptr;
	hr = dxcCompiler->Compile(
		&shaderSourceBuffer,	// 読み込んだファイル
		arguments,				// コンパイルオプション
		_countof(arguments),	// コンパイルオプションの数
		includeHandler,			// includeが含まれた諸々
		IID_PPV_ARGS(&shaderResult)// コンパイル結果
	);
	// コンパイルエラーではなく、dxcが起動できないなど致命的な状況
	assert(SUCCEEDED(hr));

	// 警告、エラーが出てたらログに出して止める
	Microsoft::WRL::ComPtr<IDxcBlobUtf8> shaderError = nullptr;
	shaderResult->GetOutput(DXC_OUT_ERRORS, IID_PPV_ARGS(&shaderError), nullptr);
	if (shaderError != nullptr && shaderError->GetStringLength() != 0) {
		Logger::Log(shaderError->GetStringPointer());
		assert(false);
	}

	// コンパイル結果から実行用のバイナリ部分を取得
	Microsoft::WRL::ComPtr<ID3DBlob> shaderBlob = nullptr;
	hr = shaderResult->GetOutput(DXC_OUT_OBJECT, IID_PPV_ARGS(&shaderBlob), nullptr);
	assert(SUCCEEDED(hr));
	// 成功したログを出す
	Logger::Log(Logger::ConvertString(std::format(L"Compile Succeeded,path:{},profile:{}\n", filePath, profile)));

	// 実行用のバイナリを追加
	return shaderBlob;
}
