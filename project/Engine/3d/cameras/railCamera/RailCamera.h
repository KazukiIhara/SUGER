#pragma once

#include <vector>

#include "3d/cameras/camera/Camera.h"
#include "math/function/MathFunction.h"

class RailCamera :public Camera {
public:
	RailCamera() = default;
	~RailCamera() = default;

	void Initialize()override;
	void Update()override;

private:
	// スプライン曲線制御点
	std::vector<Vector3> controlPoints_;
	// レールカメラ補間変数
	float t_ = 0.0f;
};
