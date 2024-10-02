#pragma once

#include <cstdint>
#include <Windows.h>

class WindowManager {
public: // 静的メンバ変数
	// クライアント領域
	static const uint32_t kClientWidth = 1280; // クライアント領域の横幅
	static const uint32_t kClientHeight = 720; // クライアント領域の縦幅

public: // 公開メンバ関数
	WindowManager() = default;
	~WindowManager() = default;

	// 初期化
	void Initialize();
	// メッセージの処理
	bool ProcessMessage();
	// 終了処理
	void Finalize();

	// ウィンドウハンドルの取得
	HWND GetHwnd() const {
		return hwnd_;
	}
	// ウィンドウクラスの取得
	WNDCLASS GetWndClass() const {
		return wc_;
	}
private:
	// ゲームウィンドウの作成
	void CreateGameWindow(const wchar_t* title = L"DirectXGame", UINT windowStyle = WS_OVERLAPPEDWINDOW,
		int32_t clientWidth = kClientWidth, int32_t clientHeight = kClientHeight);
	// ゲームウィンドウの破棄
	void TerminateGameWindow();

public: // 静的メンバ関数
	// ウィンドウプロシージャ
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

private: // メンバ変数
	// Window関連
	HWND hwnd_ = nullptr; // ウィンドウハンドル
	WNDCLASS wc_{};	// ウィンドウクラス

};