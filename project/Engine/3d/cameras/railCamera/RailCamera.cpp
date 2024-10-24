#include "RailCamera.h"

void RailCamera::Initialize() {
	// 基本的なカメラの初期化
	Camera::Initialize();
	transform_.rotate_ = { 0.0f,0.0f,0.0f };

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

	// 現在座標を求める
	transform_.translate_ = CatmullRomSpline(controlPoints_, t_) + translateOffset_;

	// target 座標を求める
	Vector3 target = CatmullRomSpline(controlPoints_, t_ +targetT_) + translateOffset_; // 少し先の位置をターゲットに設定

	// 差分ベクトルを計算
	Vector3 direction = Normalize(target - worldPos_);

	// 回転を適用
	transform_.rotate_.y = std::atan2(direction.x, direction.z);
	transform_.rotate_.x = std::atan2(-direction.y, std::sqrtf(direction.x * direction.x + direction.z * direction.z)) + rotateXOffset_;

}

void RailCamera::PushBackControlPoint(const Vector3& point) {
	controlPoints_.push_back(point);
}
