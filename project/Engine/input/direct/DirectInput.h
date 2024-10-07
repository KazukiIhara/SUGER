#pragma once
// Include
#define DIRECTINPUT_VERSION	0x0800 // DirectInputのバージョン設定
#include <dinput.h>
#include "directX/includes/ComPtr.h"

// pragma comment
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

// 前方宣言
class WindowManager;

// DirectInputクラス
class DirectInput {
public:
	// 初期化
	void Initialize(WindowManager* windowManager);
	// 更新
	void Update();

	// キーの押下をチェック
	// 押しているとき
	bool PushKey(BYTE keyNumber);
	// 押されたとき
	bool TriggerKey(BYTE keyNumber);
	// 離したとき
	bool ReleaseKey(BYTE keyNumber);

private:
	void SetWindowManager(WindowManager* windowManager);

private:

	// WindowManagerのポインタ
	WindowManager* windowManager_ = nullptr;
	// インスタンス
	ComPtr <IDirectInput8> directInput = nullptr;
	// キーボード
	ComPtr <IDirectInputDevice8> keybord = nullptr;

	// 現在フレームのキー入力
	BYTE key[256];
	// 1フレーム前のキー入力
	BYTE preKey[256];
};
