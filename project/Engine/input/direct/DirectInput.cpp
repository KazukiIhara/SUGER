// Include
#include <cassert>

// MyHedder
#include "DirectInput.h"
#include "manager/window/WindowManager.h"
#include "debugTools/logger/Logger.h"

void DirectInput::Initialize(WindowManager* windowManager) {

	// WindowManagerのインスタンスのセット
	SetWindowManager(windowManager);

	// DirectInputの初期化
	HRESULT result = S_FALSE;
	directInput = nullptr;
	result = DirectInput8Create(
		windowManager_->GetWndClass().hInstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&directInput, nullptr
	);
	assert(SUCCEEDED(result));

	// キーボードデバイスの生成
	keybord = nullptr;
	result = directInput->CreateDevice(GUID_SysKeyboard, &keybord, NULL);
	assert(SUCCEEDED(result));

	// 入力データ形式のセット
	result = keybord->SetDataFormat(&c_dfDIKeyboard); // 標準形式
	assert(SUCCEEDED(result));

	// 排他制御レベルのセット
	result = keybord->SetCooperativeLevel(windowManager_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void DirectInput::Update() {
	// キーボード情報の取得開始
	keybord->Acquire();

	// 前フレームのキーの入力状態を取得する
	memcpy(preKey, key, sizeof(key));

	// キーボードの入力状態を取得
	keybord->GetDeviceState(sizeof(key), key);

}

bool DirectInput::PushKey(BYTE keyNumber) {
	// 指定キーを押して入ればtrueを返す
	if (key[keyNumber]) {
		return true;
	}
	return false;
}

bool DirectInput::TriggerKey(BYTE keyNumber) {
	// 1フレーム前に指定キーを入力しておらず、現在フレームで入力していればtrueを返す
	if (!preKey[keyNumber] && key[keyNumber]) {
		return true;
	}
	return false;
}

bool DirectInput::HoldKey(BYTE keyNumber) {
	// 1フレーム前に指定キーを入力しており、現在フレームも入力していればtrueを返す
	if (preKey[keyNumber] && key[keyNumber]) {
		return true;
	}
	return false;
}

bool DirectInput::ReleaseKey(BYTE keyNumber) {
	// 1フレーム前に指定キーを入力しており、現在フレームで入力していなければtrueを返す
	if (preKey[keyNumber] && !key[keyNumber]) {
		return true;
	}
	return false;
}

void DirectInput::SetWindowManager(WindowManager* windowManager) {
	windowManager_ = windowManager;
}
