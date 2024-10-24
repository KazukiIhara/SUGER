#include "WindowManager.h"

#include "manager/imgui/ImGuiManager.h"

void WindowManager::Initialize() {
	// システムタイマー分解能をあげる
	timeBeginPeriod(1);
	// ゲームウィンドウの作成
	CreateGameWindow();
}

void WindowManager::CreateGameWindow(const wchar_t* title, UINT windowStyle, int32_t clientWidth, int32_t clientHeight) {

	// COMの初期化
	HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);

	// ウィンドウプロシージャ
	wc_.lpfnWndProc = WindowProc;
	// ウィンドウクラス名
	wc_.lpszClassName = title;
	// インスタンスハンドル
	wc_.hInstance = GetModuleHandle(nullptr);
	// カーソル
	wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);

	// ウィンドウクラスを登録する
	RegisterClass(&wc_);

	// ウィンドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc{ 0,0,kClientWidth,kClientHeight };

	// クライアント領域を元に実際のサイズにwrcを変更してもらう
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	// ウィンドウの生成
	hwnd_ = CreateWindow
	(
		wc_.lpszClassName,		// 利用するクラス名
		L"DirectXGame",			// タイトルバーの文字
		WS_OVERLAPPEDWINDOW,	// よく見るウィンドウスタイル
		CW_USEDEFAULT,			// 表示X座標
		CW_USEDEFAULT,			// 表示Y座標
		wrc.right - wrc.left,	// ウィンドウ横幅
		wrc.bottom - wrc.top,	// ウィンドウ縦幅
		nullptr,				// 親ウィンドウハンドル
		nullptr,				// メニューハンドル
		wc_.hInstance,			// インスタンスハンドル
		nullptr					// オプション
	);

	// ウィンドウを表示する
	ShowWindow(hwnd_, SW_SHOW);
}

void WindowManager::TerminateGameWindow() {
	// ウィンドウクラスを登録解除
	UnregisterClass(wc_.lpszClassName, wc_.hInstance);
	// COM 終了
	CoUninitialize();
}

bool WindowManager::ProcessMessage() {
	// メッセージ
	MSG msg{};

	// ウィンドウにメッセージが来ていたら最優先で処理
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// ウィンドウのxボタンが押されるまでループ
	if (msg.message == WM_QUIT) {
		return true;
	}

	return false;
}

void WindowManager::Finalize() {
	// ウィンドウを閉じる
	CloseWindow(hwnd_);
	// ウィンドウを破棄
	TerminateGameWindow();
}

LRESULT WindowManager::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	/*ImGuiでもマウス操作ができるようになるやつ*/
	if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
		return true;
	}

	// メッセージに応じてゲーム固有の処理を行う
	switch (msg) {
		// ウィンドウが破棄された
		case WM_DESTROY:
			// OSに対してアプリの終了を伝える
			PostQuitMessage(0);
			return 0;
	}
	// 標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

