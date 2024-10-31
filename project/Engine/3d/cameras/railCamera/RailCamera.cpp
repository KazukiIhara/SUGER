#include "RailCamera.h"

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
	// 1.0にたどり着くまで補間変数に加算
	if (t_ < 1.0f) {
		t_ += speed_;
	}
	// １.0fを超えないようにする
	if (t_ > 1.0f) {
		t_ = 1.0f;
	}

	// 現在座標を求める
	transform_.translate_ = CatmullRomSpline(controlPoints_, t_);

	// 目標のtの値を求める
	float targetT = t_ + targetOffset_;
	// 目標のtの値が1.0fを超えるときは修正
	if (targetT > 1.0f) {
		targetT = 1.0f;
	}

	// target 座標を求める
	Vector3 target = CatmullRomSpline(controlPoints_, targetT); // 少し先の位置をターゲットに設定

	// 差分ベクトルを計算
	Vector3 direction = Normalize(target - worldPos_);


	// 回転を適用
	transform_.rotate_.y = std::atan2(direction.x, direction.z);
	transform_.rotate_.x = std::atan2(-direction.y, std::sqrtf(direction.x * direction.x + direction.z * direction.z)) + rotateXOffset_;


}

void RailCamera::PushBackControlPoint(const Vector3& point) {
	controlPoints_.push_back(point);
}
