#include "DirectXManager.h"

// C++ 
#include <thread>

// DirectX
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

// MyHedder
#include "WindowManager.h"
#include "Logger.h"

void DirectXManager::Initialize(WindowManager* windowManager, bool enableDebugLayer) {
	// WindowManagerのインスタンスをセット
	SetWindowManager(windowManager);
	// FPS固定処理初期化
	InitializeFixFPS();
	// DXGIデバイスの初期化
	dxgi_ = std::make_unique<DXGIManager>();
	dxgi_->Initialize();
	// コマンド関連の初期化
	InitializeCommand();
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
	commandList_->ResourceBarrier(1, &barrier_);

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
	commandList_->ResourceBarrier(1, &barrier_);

	// コマンドのクローズ
	commandList_->Close();

	// GPUにコマンドリストの実行を行わせる
	ID3D12CommandList* commandLists[] = { commandList_.Get() };
	commandQueue_->ExecuteCommandLists(1, commandLists);
	// GPUとOSに画面の交換を行うよう通知する
	swapChain_->Present(1, 0);

	// Fenceの値を更新し、GPUがここまでたどり着いたときに、Fenceの値を指定した値に代入するようにSignalを送る
	commandQueue_->Signal(fence_.Get(), ++fenceValue_);
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

	// FPS固定更新処理
	UpdateFixFPS();

	// 次のフレーム用のコマンドリストを準備
	hr_ = commandAllocator_->Reset();
	assert(SUCCEEDED(hr_));
	hr_ = commandList_->Reset(commandAllocator_.Get(), nullptr);
	assert(SUCCEEDED(hr_));
}

DXGIManager* DirectXManager::GetDXGIManager() const {
	return dxgi_.get();
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

void DirectXManager::InitializeCommand() {
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

void DirectXManager::CreateSwapChain() {
	swapChainDesc_.Width = WindowManager::kClientWidth;				// 画面の幅、ウィンドウのクライアント領域を同じものにしておく
	swapChainDesc_.Height = WindowManager::kClientHeight;				// 画面の高さ、ウィンドウのクライアント領域を同じものしておく
	swapChainDesc_.Format = DXGI_FORMAT_R8G8B8A8_UNORM;			// 色形式
	swapChainDesc_.SampleDesc.Count = 1;						// マルチサンプルしない
	swapChainDesc_.BufferCount = 2;								// ダブルバッファ
	swapChainDesc_.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;	// モニタにうつしたら、中身を破棄

	// コマンドキュー、ウィンドウハンドル、設定を渡して生成する
	hr_ = dxgi_->GetFactory()->CreateSwapChainForHwnd(commandQueue_.Get(), windowManager_->GetHwnd(), &swapChainDesc_,
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
	commandList_->ClearDepthStencilView(dsvHandle_, D3D12_CLEAR_FLAG_DEPTH, 1.0f, 0, 0, nullptr);
}

void DirectXManager::ClearRenderTarget(float clearColor[]) {
	// これから書き込むバックバッファインデックスを取得
	backBufferIndex_ = swapChain_->GetCurrentBackBufferIndex();
	// 指定した色で画面全体をクリアする
	commandList_->ClearRenderTargetView(rtvHandles_[backBufferIndex_], clearColor, 0, nullptr);
}

void DirectXManager::SetRenderTargets() {
	// これから書き込むバックバッファインデックスを取得
	backBufferIndex_ = swapChain_->GetCurrentBackBufferIndex();
	dsvHandle_ = dsvDescriptorHeap_->GetCPUDescriptorHandleForHeapStart();
	// 描画先のRTVとDSVをを設定する
	commandList_->OMSetRenderTargets(1, &rtvHandles_[backBufferIndex_], false, &dsvHandle_);
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
	commandList_->RSSetViewports(1, &viewport);
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
	commandList_->RSSetScissorRects(1, &scissorRect);
}

void DirectXManager::InitializeFixFPS() {
	// 現在時間を記録する
	reference_ = std::chrono::steady_clock::now();
}

void DirectXManager::UpdateFixFPS() {
	// 1/60秒ぴったりの時間
	const std::chrono::microseconds kMinTime(uint64_t(1000000.0f / 60.0f));
	// 1/60秒よりわずかに短い時間
	const std::chrono::microseconds kMinCheckTime(uint64_t(1000000.0f / 65.0f));

	// 現在時間を取得する
	std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
	// 前回記録からの経過時間を取得する
	std::chrono::microseconds elapsed =
		std::chrono::duration_cast<std::chrono::microseconds>(now - reference_);

	// 1/60秒(よりわずかに短い時間)経っていない場合
	if (elapsed < kMinTime) {
		// 1/60秒経過するまで微小なスリープを繰り返す
		while (std::chrono::steady_clock::now() - reference_ < kMinCheckTime) {
			// 1マイクロ秒スリープ
			std::this_thread::sleep_for(std::chrono::microseconds(1));
		}
	}
	// 現在の時間を記録する
	reference_ = std::chrono::steady_clock::now();
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
