#pragma once

#define DIRECTINPUT_VERSION	0x0800 // DirectInputのバージョン設定
// Include
#include <dinput.h>
#include "directX/includes/ComPtr.h"
#include "enum/DirectInputEnum.h"

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
	// 押し続けているとき
	bool HoldKey(BYTE keyNumber);
	// 離したとき
	bool ReleaseKey(BYTE keyNumber);
	
	// ボタンを押している
	bool PushButton(int buttonNumber);
	// ボタンが押された
	bool TriggerButton(int buttonNumber);
	// ボタンを押し続けている
	bool HoldButton(int buttonNumber);
	// ボタンを離した
	bool ReleaseButton(int buttonNumber);

	// 左スティックのX軸位置を取得（-1000～1000の範囲にスケーリング）
	int GetLeftStickX() const;
	// 左スティックのY軸位置を取得（-1000～1000の範囲にスケーリング）
	int GetLeftStickY() const;

	// 右スティックのX軸位置を取得（-1000～1000の範囲にスケーリング）
	int GetRightStickX() const;
	// 右スティックのY軸位置を取得（-1000～1000の範囲にスケーリング）
	int GetRightStickY() const;

	// 左トリガーの位置を取得（0～1000の範囲）
	int GetLeftTrigger() const;
	// 右トリガーの位置を取得（0～1000の範囲）
	int GetRightTrigger() const;

	// 方向キーの取得
	bool IsPadUp() const;
	bool IsPadRight() const;
	bool IsPadDown() const;
	bool IsPadLeft() const;

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
	// ゲームパッド
	ComPtr<IDirectInputDevice8> gamepad = nullptr;
	// 現在フレームのパッド入力
	DIJOYSTATE gamepadState;
	// 1フレーム前のパッド入力
	DIJOYSTATE preGamepadState;

};
