// DirectX 12でルートシグネチャとグラフィックスパイプラインの管理を行う

// GraphicsPipelineManagerクラスのヘッダーファイルをインクルード
#include "GraphicsPipelineManager.h"

// 標準C++ヘッダー
#include <cassert>
#include <format>  

// DirectXのシェーダーコンパイラをリンク
#pragma comment(lib,"dxcompiler.lib")

// カスタムヘッダー
#include "debugTools/logger/Logger.h"  // ログ出力に使用
#include "manager/directX/DirectXManager.h"  // DirectXManager依存関係

// GraphicsPipelineManagerの初期化処理
// DirectXManagerを使用して2D用のグラフィックスパイプラインを設定
void GraphicsPipelineManager::Initialize(DirectXManager* directXManager) {
	// 2Dオブジェクト描画用のグラフィックスパイプラインを生成
	object2dGraphicsPipeline_ = std::make_unique<Object2DGraphicsPipeline>();

	// 2DグラフィックスパイプラインをDirectXManagerを使って初期化
	object2dGraphicsPipeline_->Initialize(directXManager);

	// 2Dオブジェクト描画用のルートシグネチャを設定
	SetRootSignature(kObject2d);

	// 2D描画用のグラフィックスパイプラインステートを設定
	SetGraphicsPipeline(kObject2d);
}

// 指定されたパイプラインステートに対応するルートシグネチャを取得する
ID3D12RootSignature* GraphicsPipelineManager::GetRootSignature(PipelineState pipelineState) {
	// 該当するパイプラインステートのルートシグネチャを返す
	return rootSignatures_[pipelineState].Get();
}

// 指定されたパイプラインステートとブレンドモードに対応するパイプラインステートオブジェクトを取得する
ID3D12PipelineState* GraphicsPipelineManager::GetPipelineState(PipelineState pipelineState, BlendMode blendMode) {
	// 該当するパイプラインステートとブレンドモードに対応するパイプラインステートオブジェクトを返す
	return graphicsPipelineStates_[pipelineState][blendMode].Get();
}

// 指定されたパイプラインステートに対応するルートシグネチャを設定する
void GraphicsPipelineManager::SetRootSignature(PipelineState pipelineState) {
	// パイプラインステートごとに対応するルートシグネチャを設定
	switch (pipelineState) {
	case kObject2d:
		// 2Dオブジェクト描画用のルートシグネチャを設定
		rootSignatures_[pipelineState] = object2dGraphicsPipeline_->GetRootSignature();
		break;

		// 他のパイプラインステートが追加された場合はここに追加
	}
}

// 指定されたパイプラインステートに対応するグラフィックスパイプラインステートを設定する
void GraphicsPipelineManager::SetGraphicsPipeline(PipelineState pipelineState) {
	// パイプラインステートごとに対応するグラフィックスパイプラインを設定
	switch (pipelineState) {
	case kObject2d:
		// 各ブレンドモードに対応するパイプラインステートを設定
		for (int mode = kBlendModeNone; mode <= kBlendModeScreen; ++mode) {
			graphicsPipelineStates_[pipelineState][mode] = object2dGraphicsPipeline_->GetPipelineState(static_cast<BlendMode>(mode));
		}
		break;

		// 他のパイプラインステートが追加された場合はここに追加
	}
}
