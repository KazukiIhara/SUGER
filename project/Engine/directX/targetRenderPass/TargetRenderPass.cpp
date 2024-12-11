#include "TargetRenderPass.h"

#include <cassert>

#include "directX/command/DirectXCommand.h"
#include "directX/swapChain/SwapChain.h"
#include "directX/depthStencil/DepthStencil.h"

void TargetRenderPass::Initialize(DirectXCommand* command, SwapChain* swapChain, DepthStencil* depthStencil) {
	SetCommand(command);
	SetSwapChain(swapChain);
	SetDepthStencil(depthStencil);
}

void TargetRenderPass::SetRenderTarget() {
	// スワップチェーンの現在のバックバッファのRTVハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE swapChainRTVHandle = swapChain_->GetCurrentBackBufferRTVHandle();
	// デプスステンシルのDSVハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE dsvhandle = depthStencil_->GetDepthStencilResorceCPUHandle();
	// 描画先のRTVとDSVを指定
	command_->GetList()->OMSetRenderTargets(1, &swapChainRTVHandle, false, &dsvhandle);
}

void TargetRenderPass::ClearRenderTarget(float clearColor[]) {
	// スワップチェーンの現在のバックバッファのRTVハンドルを取得
	D3D12_CPU_DESCRIPTOR_HANDLE swapChainRTVHandle = swapChain_->GetCurrentBackBufferRTVHandle();
	// 指定した色で画面全体をクリアする
	command_->GetList()->ClearRenderTargetView(swapChainRTVHandle, clearColor, 0, nullptr);
}

void TargetRenderPass::SetCommand(DirectXCommand* command) {
	assert(command);
	command_ = command;
}

void TargetRenderPass::SetSwapChain(SwapChain* swapChain) {
	assert(swapChain);
	swapChain_ = swapChain;
}

void TargetRenderPass::SetDepthStencil(DepthStencil* depthStencil) {
	assert(depthStencil);
	depthStencil_ = depthStencil;
}
