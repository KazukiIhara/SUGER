#pragma once
// MyHedder
#include "math/function/MathFunction.h"

// シェーダーに送るカメラ座標
struct sCameraForGPU {
	Vector3 worldPosition;
	float padding;
};