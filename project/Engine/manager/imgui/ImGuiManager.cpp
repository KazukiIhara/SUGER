// This
#include "ImGuiManager.h"

// MyHedder
#include "WindowManager.h"
#include "DirectXManager.h"
#include "DirectXCommand.h"
#include "SRVManager.h"

void ImGuiManager::Initialize(WindowManager* windowManager, DirectXManager* directXManager, SRVManager* srvManager) {
	
	// インスタンスのセット
	SetWindowManager(windowManager);
	SetDirectXManager(directXManager);
	SetDirectXCommand(directXManager_->GetDirectXCommand());
	SetSrvManager(srvManager);
	
	/*ImGuiの初期化*/
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(windowManager_->GetHwnd());
	ImGui_ImplDX12_Init(directXManager_->GetDXGIManager()->GetDevice(),
		directXManager_->GetSwapChainDesc().BufferCount,
		directXManager_->GetRTVDesc().Format,
		srvManager_->GetDescriptorHeap(),
		srvManager_->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
		srvManager_->GetDescriptorHeap()->GetGPUDescriptorHandleForHeapStart()
	);
	srvManager_->Allocate();
}

void ImGuiManager::BeginFrame() {
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void ImGuiManager::EndFrame() {
	// ImGui内部コマンドの生成
	ImGui::Render();
}

void ImGuiManager::Draw() {
	// 実際のCommandListのImGuiの描画コマンドを積む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), dxCommand_->GetList());
}

void ImGuiManager::Finalize() {
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::SetWindowManager(WindowManager* windowManager) {
	windowManager_ = windowManager;
}

void ImGuiManager::SetDirectXManager(DirectXManager* directXManager) {
	directXManager_ = directXManager;
}

void ImGuiManager::SetDirectXCommand(DirectXCommandManager* dxCommand) {
	dxCommand_ = dxCommand;
}

void ImGuiManager::SetSrvManager(SRVManager* srvManager) {
	srvManager_ = srvManager;
}