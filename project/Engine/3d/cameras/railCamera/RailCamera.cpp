#include "RailCamera.h"

#include "imgui.h"

#include <cmath> 
#include <algorithm>

void RailCamera::Initialize() {
	// 基本的なカメラの初期化
	Camera::Initialize();
	transform_.translate_ = { 0.0f,0.0f,0.0f };
	transform_.rotate_ = { 0.0f,0.0f,0.0f };

	// カメラの値を初期化で変更した場合、更新処理に入る前に一度行列を更新する
	Camera::Update();

	// 補間用変数をリセット
	t_ = 0.0f;
}

void RailCamera::Update() {
	// レールを走らせる
	RunRail();

	// 基本的なカメラの更新
	Camera::Update();
}

void RailCamera::RunRail() {
    // 世界の上方向ベクトルを設定
    Vector3 worldUp = { 0.0f, 1.0f, 0.0f };

    // 初期のカメラ上方向を世界の上方向と同じに設定
    static Vector3 currentUp_ = worldUp;

    // t_の更新処理
    if (t_ < 1.0f) {
        t_ += speed_;
    }
    if (t_ > 1.0f) {
        t_ = 1.0f;
    }

    // 現在位置の計算
    transform_.translate_ = CatmullRomSpline(controlPoints_, t_);

    // わずかに先の位置を取得して進行方向ベクトルを計算
    float nextT = t_ + 0.01f;
    if (nextT > 1.0f) nextT = 1.0f;

    Vector3 nextPosition = CatmullRomSpline(controlPoints_, nextT);
    Vector3 forward = Normalize(nextPosition - transform_.translate_); // 接線ベクトル（進行方向）

    // 前回のカメラ上方向に基づき、進行方向から右方向を計算
    Vector3 right = Normalize(Cross(currentUp_, forward));
    Vector3 calculatedUp = Cross(forward, right); // 進行方向に基づく上方向を計算

    // X軸のみに基づいて角度差を計算
    float angleDifferenceX = std::atan2(calculatedUp.y, calculatedUp.z) - std::atan2(worldUp.y, worldUp.z);
    angleDifferenceX = std::fabs(angleDifferenceX * (180.0f / std::numbers::pi_v<float>)); // ラジアンを度に変換して絶対値を取る

    // 角度差に基づく補正
    if (angleDifferenceX < 50.0f) { // 10度未満の場合、世界の上方向を考慮して補正
        currentUp_ = Lerp(currentUp_, worldUp, 0.1f); // 世界の上方向に補正（補間率は0.1）
    } else { // 10度以上の場合は現在の上方向を維持
        currentUp_ = calculatedUp;
    }

    // ImGuiでデバッグ用に角度を出力
    ImGui::Text("X-Axis Angle Difference: %f", angleDifferenceX);

    // クォータニオンで回転を設定
    Quaternion rotationQuat = QuaternionLookRotation(forward, currentUp_);

    // クォータニオンをオイラー角に変換して設定
    transform_.rotate_ = QuaternionToEulerAngles(rotationQuat);
}

void RailCamera::PushBackControlPoint(const Vector3& point) {
	controlPoints_.push_back(point);
}
