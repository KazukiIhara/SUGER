// This
// This
#include "ImGuiManager.h"

// MyHedder
#include "WindowManager.h"

void ImGuiManager::Initialize() {

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
	
}

void ImGuiManager::Finalize() {
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
