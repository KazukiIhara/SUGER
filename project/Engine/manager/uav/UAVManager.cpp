#include "UAVManager.h"

// MyHedder
#include "manager/directX/DirectXManager.h"
#include "manager/dxgi/DXGIManager.h"
#include "directX/command/DirectXCommand.h"

void UAVManager::Initialize(DirectXManager* directX) {
	// DirectXManagerのインスタンスを取得
	SetDirectXManager(directX);
	// デスクリプタヒープの作成
	descriptorHeap_ = DirectXManager::CreateDescriptorHeap(directX_->GetDevice(), D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, kMaxUAVCount, true);
	// デスクリプタ一個分のサイズを取得して記録
	descriptorSize_ = directX_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
}

uint32_t UAVManager::Allocate() {
	int index = useIndex;
	useIndex++;
	return index;
}

D3D12_CPU_DESCRIPTOR_HANDLE UAVManager::GetDescriptorHandleCPU(uint32_t index) {
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize_ * index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE UAVManager::GetDescriptorHandleGPU(uint32_t index) {
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize_ * index);
	return handleGPU;
}

void UAVManager::CreateUavStructuredBuffer(uint32_t uavIndex, ID3D12Resource* pResource, uint32_t numElements, UINT structureByteStride) {
	D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc{};
	uavDesc.Format = DXGI_FORMAT_UNKNOWN;
	uavDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
	uavDesc.Buffer.FirstElement = 0;
	uavDesc.Buffer.NumElements = numElements;
	uavDesc.Buffer.CounterOffsetInBytes = 0;
	uavDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
	uavDesc.Buffer.StructureByteStride = structureByteStride;

	directX_->GetDevice()->CreateUnorderedAccessView(
		pResource, nullptr, &uavDesc, GetDescriptorHandleCPU(uavIndex));
}

bool UAVManager::IsLowerUavMax() {
	return useIndex < kMaxUAVCount;
}

void UAVManager::PreCommand() {	
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeaps[] = { descriptorHeap_ };
	directX_->GetCommandList()->SetDescriptorHeaps(1, descriptorHeaps->GetAddressOf());
}

void UAVManager::SetComputeRootDescriptorTable(UINT rootParameterIndex, uint32_t uavIndex) {
	directX_->GetCommandList()->SetComputeRootDescriptorTable(rootParameterIndex, GetDescriptorHandleGPU(uavIndex));
}

ID3D12DescriptorHeap* UAVManager::GetDescriptorHeap() const {
	return descriptorHeap_.Get();
}

uint32_t UAVManager::GetDescriptorSize() const {
	return descriptorSize_;
}

void UAVManager::SetDirectXManager(DirectXManager* directX) {
	directX_ = directX;
}
