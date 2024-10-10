#pragma once

#include "math/function/MathFunction.h"

// ディレクショナルライト
struct DirectionalLightData {
	Vector4 color; //ライトの色
	Vector3 direction; //ライトの向き
	float intensity; //輝度
};

// ポイントライト
struct PointLightData {
	Vector4 color;
	Vector3 position;
	float intensity;
	float radius;
	float decay;
	float padding[2];
};

// スポットライト
struct SpotLightData {
	Vector4 color;
	Vector3 position;
	float intensity;
	Vector3 direction;
	float distance;
	float decay;
	float cosFalloffStart;
	float cosAngle;
	float padding;
};

// PunctualLight
struct PunctualLightData {
	DirectionalLightData directionalLight;
	PointLightData pointLight;
	SpotLightData spotLight;
};
