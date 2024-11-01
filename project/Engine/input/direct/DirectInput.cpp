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

	// ゲームパッドデバイスの生成
	result = directInput->CreateDevice(GUID_Joystick, &gamepad, NULL);
	if (SUCCEEDED(result)) {
		// 入力データ形式のセット
		gamepad->SetDataFormat(&c_dfDIJoystick); // 標準形式
		// 排他制御レベルのセット
		gamepad->SetCooperativeLevel(windowManager_->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	}
}

void DirectInput::Update() {
	// キーボード情報の取得開始
	keybord->Acquire();

	// 前フレームのキーの入力状態を取得する
	memcpy(preKey, key, sizeof(key));

	// キーボードの入力状態を取得
	keybord->GetDeviceState(sizeof(key), key);

	// ゲームパッド情報の取得開始
	if (gamepad) {
		gamepad->Acquire();
		preGamepadState = gamepadState; // 前フレームの状態をコピー
		gamepad->GetDeviceState(sizeof(DIJOYSTATE), &gamepadState); // 現在の状態を取得
	}
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

bool DirectInput::PushButton(int buttonNumber) {
	return (gamepadState.rgbButtons[buttonNumber] & 0x80) != 0;
}

bool DirectInput::TriggerButton(int buttonNumber) {
	return (!(preGamepadState.rgbButtons[buttonNumber] & 0x80) && (gamepadState.rgbButtons[buttonNumber] & 0x80));
}

bool DirectInput::HoldButton(int buttonNumber) {
	return ((preGamepadState.rgbButtons[buttonNumber] & 0x80) && (gamepadState.rgbButtons[buttonNumber] & 0x80));
}

bool DirectInput::ReleaseButton(int buttonNumber) {
	return ((preGamepadState.rgbButtons[buttonNumber] & 0x80) && !(gamepadState.rgbButtons[buttonNumber] & 0x80));
}

// 左スティックのX軸位置取得関数
int DirectInput::GetLeftStickX() const {
	// lXを利用して左スティックのX軸位置を取得
	return gamepadState.lX;
}

// 左スティックのY軸位置取得関数
int DirectInput::GetLeftStickY() const {
	// lYを利用して左スティックのY軸位置を取得
	return gamepadState.lY;
}

// 右スティックのX軸位置取得関数
int DirectInput::GetRightStickX() const {
	// lRxを利用して右スティックのX軸位置を取得
	return gamepadState.lRx;
}

// 右スティックのY軸位置取得関数
int DirectInput::GetRightStickY() const {
	// lRyを利用して右スティックのY軸位置を取得
	return gamepadState.lRy;
}

// 左トリガーの位置取得関数
int DirectInput::GetLeftTrigger() const {
	// lZを利用して左トリガーの値を取得
	return gamepadState.lZ;
}

// 右トリガーの位置取得関数
int DirectInput::GetRightTrigger() const {
	// lRzを利用して右トリガーの値を取得
	return gamepadState.lRz;
}

// D-Pad上の判定
bool DirectInput::IsPadUp() const {
    return gamepadState.rgdwPOV[0] == 0;
}

// D-Pad右の判定
bool DirectInput::IsPadRight() const {
    return gamepadState.rgdwPOV[0] == 9000;
}

// D-Pad下の判定
bool DirectInput::IsPadDown() const {
    return gamepadState.rgdwPOV[0] == 18000;
}

// D-Pad左の判定
bool DirectInput::IsPadLeft() const {
    return gamepadState.rgdwPOV[0] == 27000;
}

void DirectInput::SetWindowManager(WindowManager* windowManager) {
	windowManager_ = windowManager;
}

