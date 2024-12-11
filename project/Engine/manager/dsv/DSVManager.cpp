#include "DSVManager.h"

#include <cassert>

#include "directX/dxgi/DXGIManager.h"
#include "directX/command/DirectXCommand.h"

void DSVManager::Initialize(DXGIManager* dxgi, DirectXCommand* command) {
	SetDXGI(dxgi);
	SetCommand(command);
	// ディスクリプタヒープの作成
	descriptorHeap_ = dxgi_->CreateDescriptorHeap(D3D12_DESCRIPTOR_HEAP_TYPE_DSV, kMaxDSVCount_, false);
	// デスクリプタ一個分のサイズを取得して記録
	descriptorSize_ = dxgi_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_DSV);
}

uint32_t DSVManager::Allocate() {
	int index = useIndex;
	useIndex++;
	return index;
}

D3D12_CPU_DESCRIPTOR_HANDLE DSVManager::GetDescriptorHandleCPU(uint32_t index) {
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize_ * index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE DSVManager::GetDescriptorHandleGPU(uint32_t index) {
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize_ * index);
	return handleGPU;
}

bool DSVManager::IsLowerViewMax() {
	return useIndex < kMaxDSVCount_;
}

ID3D12DescriptorHeap* DSVManager::GetDescriptorHeap() const {
	return descriptorHeap_.Get();
}

uint32_t DSVManager::GetDescriptorSize() const {
	return descriptorSize_;
}

void DSVManager::SetDXGI(DXGIManager* dxgi) {
	assert(dxgi);
	dxgi_ = dxgi;
}

void DSVManager::SetCommand(DirectXCommand* command) {
	assert(command);
	command_ = command;
}
