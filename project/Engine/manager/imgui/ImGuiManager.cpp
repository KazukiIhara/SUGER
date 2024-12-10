// This
#include "ImGuiManager.h"

// MyHedder
#include "manager/window/WindowManager.h"
#include "manager/directX/DirectXManager.h"
#include "directX/command/DirectXCommand.h"
#include "manager/view/ViewManager.h"

void ImGuiManager::Initialize(WindowManager* windowManager, DirectXManager* directXManager, ViewManager* srvManager) {

	// インスタンスのセット
	SetWindowManager(windowManager);
	SetDirectXManager(directXManager);
	SetSrvManager(srvManager);

	// ImGuiの初期化
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(windowManager_->GetHwnd());
	ImGui_ImplDX12_Init(directXManager_->GetDXGI()->GetDevice(),
		directXManager_->GetSwapChainDesc().BufferCount,
		directXManager_->GetRTVDesc().Format,
		srvManager_->GetDescriptorHeap(),
		srvManager_->GetDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(),
		srvManager_->GetDescriptorHeap()->GetGPUDescriptorHandleForHeapStart()
	);

	// フォントサイズ変更
	FontSetting();

	srvManager_->Allocate();
}

void ImGuiManager::FontSetting() {
	// フォントのサイズ変更処理
	ImGuiIO& io = ImGui::GetIO();
	ImFontConfig fontConfig;
	// サイズを指定
	fontConfig.SizePixels = 15.0f;
	// デフォルトフォントを再ロード
	io.Fonts->AddFontDefault(&fontConfig);
	// フォントを再構築
	io.Fonts->Build();
}

void ImGuiManager::CreatePreviewSrv() {
	// Srv作成
	
}

void ImGuiManager::BeginFrame() {
	ImGui_ImplDX12_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// ImGuiをダークテーマにする
	SetImGuiDarkTheme();
}

void ImGuiManager::EndFrame() {
	// ImGui内部コマンドの生成
	ImGui::Render();
}

void ImGuiManager::Draw() {
	// 実際のCommandListのImGuiの描画コマンドを積む
	ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), directXManager_->GetCommandList());
}

void ImGuiManager::ShowPreviewWindow() {

	
}

void ImGuiManager::Finalize() {
	ImGui_ImplDX12_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiManager::SetImGuiDarkTheme() {
	ImGuiStyle& style = ImGui::GetStyle();
	ImVec4* colors = style.Colors;

	// 基本的な背景、ウィンドウ、ボーダーの色設定
	colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_Border] = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.09f, 0.09f, 0.09f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

	// ボタン関連の色
	colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);

	// スクロールバーやチェックボックス、スライダーの色
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.35f, 0.35f, 0.35f, 1.00f);

	// メニューやポップアップの色
	colors[ImGuiCol_PopupBg] = ImVec4(0.11f, 0.11f, 0.11f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.15f, 0.15f, 0.15f, 1.00f);

	// その他のインタラクティブなUI要素
	colors[ImGuiCol_CheckMark] = ImVec4(0.71f, 0.71f, 0.71f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.40f, 0.40f, 0.40f, 1.00f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.45f, 0.45f, 0.45f, 1.00f);

	// タブとテキストの色
	colors[ImGuiCol_Tab] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.25f, 0.25f, 0.25f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.24f, 0.24f, 0.24f, 1.00f);
}

void ImGuiManager::SetWindowManager(WindowManager* windowManager) {
	windowManager_ = windowManager;
}

void ImGuiManager::SetDirectXManager(DirectXManager* directXManager) {
	directXManager_ = directXManager;
}

void ImGuiManager::SetSrvManager(ViewManager* srvManager) {
	srvManager_ = srvManager;
}