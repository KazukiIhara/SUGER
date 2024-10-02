#pragma once

// WindowsAPI
#include <Windows.h>

// imgui
#include "externals/imgui/imgui.h"
#include "externals/imgui/imgui_impl_dx12.h"
#include "externals/imgui/imgui_impl_win32.h"

// 前方宣言
class WindowManager;
class DirectXManager;
class SrvManager;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam
);

// imguiマネージャ
class ImGuiManager {
public: // インスタンスセット関数
	void SetWindowManager(WindowManager* windowManager) {
		windowManager_ = windowManager;
	}
	void SetDirectXCommon(DirectXManager* directXManager) {
		directXManager_ = directXManager;
	}
	void SetSrvManager(SrvManager* srvManager) {
		srvManager_ = srvManager;
	}
public: // 公開メンバ関数
	ImGuiManager() = default;
	~ImGuiManager() = default;

	// 初期化
	void Initialize();

	// 更新処理の先頭に呼び出す処理
	void BeginFrame();

	// 更新処理の最後に呼び出す処理
	void EndFrame();

	// 描画
	void Draw();

	// ImGuiの終了処理
	void Finalize();

private: // インスタンスを受け取る変数
	// WinAPI
	WindowManager* windowManager_ = nullptr;
	// DirectXCommon
	DirectXManager* directXManager_ = nullptr;
	// SrvManager
	SrvManager* srvManager_ = nullptr;
};

