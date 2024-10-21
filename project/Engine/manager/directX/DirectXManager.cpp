#include "DirectXManager.h"

// C++ 
#include <thread>

// MyHedder
#include "manager/window/WindowManager.h"
#include "debugTools/logger/Logger.h"

void DirectXManager::Initialize(WindowManager* windowManager, bool enableDebugLayer) {
	// WindowManagerのインスタンスをセット
	SetWindowManager(windowManager);

	// DXGIデバイスの初期化
	dxgi_ = std::make_unique<DXGIManager>();
	dxgi_->Initialize();

	// コマンドの初期化
	dxCommand_ = std::make_unique<DirectXCommand>();
	dxCommand_->Initialize(dxgi_.get());

	// FPS固定処理の初期化
	fixFPS_ = std::make_unique<FixFPS>();
	fixFPS_->Initialize();

	// スワップチェーンの生成
	CreateSwapChain();
	// レンダーターゲットの生成
	CreateRenderTargetView();
	// 深度バッファの生成
	CreateDepthStencilView();
	// フェンスの生成
	CreateFence();
}

void DirectXManager::PreDraw() {
	// これから書き込むバックバッファインデックスを取得
	backBufferIndex_ = swapChain_->GetCurrentBackBufferIndex();
	// TransitionBarrierの設定
	// 今回のバリアはTransition
	barrier_.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	// Noneにしておく
	barrier_.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	// バリアを張る対象のリソース。現在のバックバッファに対して行う
	barrier_.Transition.pResource = swapChainResources_[backBufferIndex_].Get();
	// 遷移前のResourceState
	barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
	// 遷移後のResourceState
	barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;
	// TransitionBarrierを張る
	dxCommand_->GetList()->ResourceBarrier(1, &barrier_);

	// レンダーターゲット設定
	SetRenderTargets();

	// 深度クリア
	ClearDepthView();

	// 全画面クリア
	float clearColor[] = { 0.05f,0.05f,0.05f,1.0f };
	ClearRenderTarget(clearColor);

	// ビューポート設定
	SettingViewport();

	// シザー矩形設定
	SettingScissorRect();
}

void DirectXManager::PostDraw() {
	// 画面に書く処理はすべて終わり、画面に映すので状態を遷移
	// 今回はRenderTargetからPresentにする
	barrier_.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
	barrier_.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
	// TransitionBarrierを張る
	dxCommand_->GetList()->ResourceBarrier(1, &barrier_);

	// GPUにコマンドリストの実行を行わせる
	KickCommand();

	// GPUとOSに画面の交換を行うよう通知する
	swapChain_->Present(1, 0);

	// GPUを待機
	WaitGPU();

	// 次フレーム用のコマンドリストを準備
	ResetCommandList();

	// FPS固定更新処理
	fixFPS_->Update();
}

void DirectXManager::KickCommand() {
	HRESULT hr = S_FALSE;
	// commandClose
	dxCommand_->GetList()->Close();

	// GPUにコマンドリストの実行を行わせる
	Microsoft::WRL::ComPtr<ID3D12CommandList> commandLists[] = { dxCommand_->GetList() };
	dxCommand_->GetQueue()->ExecuteCommandLists(1, commandLists->GetAddressOf());
}

void DirectXManager::WaitGPU() {
	// Fenceの値を更新し、GPUがここまでたどり着いたときに、Fenceの値を指定した値に代入するようにSignalを送る
	dxCommand_->GetQueue()->Signal(fence_.Get(), ++fenceValue_);
	// Fenceの値が指定したSingnal値にたどり着いているか確認する
	// GetCompletedValueの初期値はFence作成時に渡した初期値
	if (fence_->GetCompletedValue() < fenceValue_) {
		// FenceのSignalを待つためのイベントを作成する
		HANDLE fenceEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
		// 指定したSignalにたどり着いていないので、たどりつくまでに待つようにイベントを設定する
		fence_->SetEventOnCompletion(fenceValue_, fenceEvent);
		// イベントを待つ
		WaitForSingleObject(fenceEvent, INFINITE);
	}
}

void DirectXManager::ResetCommandList() {
	// 次のフレーム用のコマンドリストを準備
	hr_ = dxCommand_->GetAllocator()->Reset();
	assert(SUCCEEDED(hr_));
	hr_ = dxCommand_->GetList()->Reset(dxCommand_->GetAllocator(), nullptr);
	assert(SUCCEEDED(hr_));
}

ID3D12Device* DirectXManager::GetDevice() {
	return dxgi_->GetDevice();
}

ID3D12CommandQueue* DirectXManager::GetCommandQueue() {
	return dxCommand_->GetQueue();
}

ID3D12CommandAllocator* DirectXManager::GetCommandAllocator() {
	return dxCommand_->GetAllocator();
}

ID3D12GraphicsCommandList* DirectXManager::GetCommandList() {
	return dxCommand_->GetList();
}

D3D12_CPU_DESCRIPTOR_HANDLE DirectXManager::GetCPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index) {
	D3D12_CPU_DESCRIPTOR_HANDLE handleCPU = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
	handleCPU.ptr += (descriptorSize * index);
	return handleCPU;
}

D3D12_GPU_DESCRIPTOR_HANDLE DirectXManager::GetGPUDescriptorHandle(ID3D12DescriptorHeap* descriptorHeap, uint32_t descriptorSize, uint32_t index) {
	D3D12_GPU_DESCRIPTOR_HANDLE handleGPU = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
	handleGPU.ptr += (descriptorSize * index);
	return handleGPU;
}

Microsoft::WRL::ComPtr<ID3D12Resource> DirectXManager::CreateBufferResource(size_t sizeInBytes) {
	HRESULT hr = S_FALSE;
	// 頂点リソース用のヒープの設定
	D3D12_HEAP_PROPERTIES uplodeHeapProperties{};
	uplodeHeapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;//UploadHeapを使う

	// マテリアル用のリソースの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	// バッファリソース。テクスチャの場合はまた別の設定をする
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = sizeInBytes;
	// バッファの場合はこれらは1にする決まり
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.SampleDesc.Count = 1;
	// バッファの場合はこれにする決まり
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	// バッファリソースを作る
	Microsoft::WRL::ComPtr<ID3D12Resource>resource = nullptr;
	hr = dxgi_->GetDevice()->CreateCommittedResource(&uplodeHeapProperties, D3D12_HEAP_FLAG_NONE,
		&resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr,
		IID_PPV_ARGS(&resource));
	assert(SUCCEEDED(hr));
	return resource;

}

Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> DirectXManager::CreateDescriptorHeap(ID3D12Device* device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible) {
	// ディスクリプタヒープの生成
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap = nullptr;
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc{};
	descriptorHeapDesc.Type = heapType;
	descriptorHeapDesc.NumDescriptors = numDescriptors;
	descriptorHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
	HRESULT hr = device->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&descriptorHeap));
	// ディスクリプターヒープが作れなかったので起動できない
	assert(SUCCEEDED(hr));
	return descriptorHeap;
}

void DirectXManager::CreateSwapChain() {
	swapChainDesc_.Width = WindowManager::kClientWidth;				// 画面の幅、ウィンドウのクライアント領域を同じものにしておく
	swapChainDesc_.Height = WindowManager::kClientHeight;				// 画面の高さ、ウィンドウのクライアント領域を同じものしておく
	swapChainDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// 色形式
	swapChainDesc_.SampleDesc.Count = 1;						// マルチサンプルしない
	swapChainDesc_.BufferCount = 2;								// ダブルバッファ
	swapChainDesc_.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// モニタにうつしたら、中身を破棄

	// コマンドキュー、ウィンドウハンドル、設定を渡して生成する
	hr_ = dxgi_->GetFactory()->CreateSwapChainForHwnd(dxCommand_->GetQueue(), windowManager_->GetHwnd(), &swapChainDesc_,
		nullptr, nullptr, reinterpret_cast<IDXGISwapChain1**>(swapChain_.GetAddressOf()));
	assert(SUCCEEDED(hr_));
}

void DirectXManager::CreateRenderTargetView() {
	// ディスクリプタヒープの生成
	// RTV用のヒープでディスクリプタの数は２。RTVはShader内で触るものではないので、ShaderVisibleはfalse
	rtvDescriptorHeap_ = CreateDescriptorHeap(dxgi_->GetDevice(), D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 2, false);
	// スワップチェーンからリソースを引っ張ってくる
	hr_ = swapChain_->GetBuffer(0, IID_PPV_ARGS(&swapChainResources_[0]));
	// うまく取得出来なければ起動できない
	assert(SUCCEEDED(hr_));
	hr_ = swapChain_->GetBuffer(1, IID_PPV_ARGS(&swapChainResources_[1]));
	assert(SUCCEEDED(hr_));

	// RTVの設定
	rtvDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;	// 出力結果をSRGBに変換して書き込む
	rtvDesc_.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;	// 2Dテクスチャとして書き込む
	// ディスクリプタの先頭を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle = rtvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart();

	// まず1つを作る
	rtvHandles_[0] = rtvStartHandle;
	dxgi_->GetDevice()->CreateRenderTargetView(swapChainResources_[0].Get(), &rtvDesc_, rtvHandles_[0]);
	// 2つ目のディスクリプタハンドルを得る
	rtvHandles_[1].ptr = rtvHandles_[0].ptr + dxgi_->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	// 2つ目を作る
	dxgi_->GetDevice()->CreateRenderTargetView(swapChainResources_[1].Get(), &rtvDesc_, rtvHandles_[1]);
}

void DirectXManager::CreateDepthStencilView() {
	// DepthStencilTextureをウィンドウのサイズで作成
	depthStencilResource_ = CreateDepthStencilTextureResource(dxgi_->GetDevice(), WindowManager::kClientWidth, WindowManager::kClientHeight);

	// DSV用のヒープでディスクリプタの数は1
	dsvDescriptorHeap_ = CreateDescriptorHeap(dxgi_->GetDevice(), D3D12_DESCRIPTOR_HEAP_TYPE_DSV, 1, false);

	// DSVの設定
	D3D12_DEPTH_STENCIL_VIEW_DESC dsvDesc{};
	dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	dsvDesc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
	// DSVHeapの先端にDSVをつくる
	dxgi_->GetDevice()->CreateDepthStencilView(depthStencilResource_.Get(), &dsvDesc, dsvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart());
}

void DirectXManager::CreateFence() {
	// 初期値0でFenceを作る
	fenceValue_ = 0;
	hr_ = dxgi_->GetDevice()->CreateFence(fenceValue_, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence_));
	assert(SUCCEEDED(hr_));
}

void DirectXManager::ClearDepthView() {
	// 指定した深度で画面全体をクリアする
	dxCommand_->GetList()->ClearDepthStencilView(dsvHandle_, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void DirectXManager::ClearRenderTarget(float clearColor[]) {
	// これから書き込むバックバッファインデックスを取得
	backBufferIndex_ = swapChain_->GetCurrentBackBufferIndex();
	// 指定した色で画面全体をクリアする
	dxCommand_->GetList()->ClearRenderTargetView(rtvHandles_[backBufferIndex_], clearColor, 0, nullptr);
}

void DirectXManager::SetRenderTargets() {
	// これから書き込むバックバッファインデックスを取得
	backBufferIndex_ = swapChain_->GetCurrentBackBufferIndex();
	dsvHandle_ = dsvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// 描画先のRTVとDSVをを設定する
	dxCommand_->GetList()->OMSetRenderTargets(1, &rtvHandles_[backBufferIndex_], false, &dsvHandle_);
}

void DirectXManager::SettingViewport() {
	// ビューポートの設定
	D3D12_VIEWPORT viewport{};
	// クライアント領域のサイズと一緒にして画面全体に表示
	viewport.Width = WindowManager::kClientWidth;
	viewport.Height = WindowManager::kClientHeight;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;

	// ビューポートを設定
	dxCommand_->GetList()->RSSetViewports(1, &viewport);
}

void DirectXManager::SettingScissorRect() {
	// シザー矩形の設定
	D3D12_RECT scissorRect{};
	// 基本的にビューポートと同じ矩形が構成されるようにする
	scissorRect.left = 0;
	scissorRect.right = WindowManager::kClientWidth;
	scissorRect.top = 0;
	scissorRect.bottom = WindowManager::kClientHeight;

	// シザー矩形を設定
	dxCommand_->GetList()->RSSetScissorRects(1, &scissorRect);
}

Microsoft::WRL::ComPtr<ID3D12Resource> DirectXManager::CreateDepthStencilTextureResource(ID3D12Device* device, int32_t width, int32_t height) {
	// 生成するResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = width;
	resourceDesc.Height = height;
	resourceDesc.MipLevels = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	resourceDesc.SampleDesc.Count = 1;
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
	resourceDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL;

	// 利用するHeapの設定
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

	// 深度値のクリア設定
	D3D12_CLEAR_VALUE depthClearValue{};
	depthClearValue.DepthStencil.Depth = 1.0f;
	depthClearValue.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;

	// Resourceの生成
	Microsoft::WRL::ComPtr<ID3D12Resource> resource = nullptr;
	HRESULT hr = device->CreateCommittedResource(
		&heapProperties,// Heapの設定
		D3D12_HEAP_FLAG_NONE,// Heapの特殊な設定。特になし。
		&resourceDesc,	// Resourceの設定
		D3D12_RESOURCE_STATE_DEPTH_WRITE,// 深度地を書き込む状態にしておく
		&depthClearValue,// Clear最適値
		IID_PPV_ARGS(&resource));// 作成するResourceポインタへのポインタ
	assert(SUCCEEDED(hr));

	return resource;
}
