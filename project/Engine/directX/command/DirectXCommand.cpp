#include "DirectXCommand.h"

#include <cassert>

void DirectXCommand::Initialize(DXGIManager* dxgi) {
	// DXGIのセット
	SetDXGIManager(dxgi);
	// コマンドキューを生成する
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc{};
	hr_ = dxgi_->GetDevice()->CreateCommandQueue(&commandQueueDesc,
		IID_PPV_ARGS(&commandQueue_));
	// コマンドキューの生成がうまくいかなかったらassert
	assert(SUCCEEDED(hr_));

	// コマンドアロケータを生成する
	hr_ = dxgi_->GetDevice()->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&commandAllocator_));
	// コマンドアロケータの生成がうまくいかなかったので起動できない
	assert(SUCCEEDED(hr_));

	// コマンドリストを生成する
	hr_ = dxgi_->GetDevice()->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, commandAllocator_.Get(), nullptr, IID_PPV_ARGS(&commandList_));
	// コマンドリストの生成がうまくいかなかったので起動できない
	assert(SUCCEEDED(hr_));
}

ID3D12CommandQueue* DirectXCommand::GetQueue() {
	return commandQueue_.Get();
}

ID3D12CommandAllocator* DirectXCommand::GetAllocator() {
	return commandAllocator_.Get();
}

ID3D12GraphicsCommandList* DirectXCommand::GetList() {
	return commandList_.Get();
}

void DirectXCommand::SetDXGIManager(DXGIManager* dxgi) {
	assert(dxgi);
	dxgi_ = dxgi;
}
