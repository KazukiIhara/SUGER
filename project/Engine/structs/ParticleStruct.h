#pragma once
#include "structs/ObjectStructs.h"

struct EmitParamater {
	Vector3 position;
	Vector3 rotate;
	Vector3 scale;
	Vector3 velocity;
	Vector4 color;
	float lifeTime;
};

struct ParticleData {
	EulerTransform3D transform;
	Vector3 velocity;
	Vector4 color;
	float lifeTime;
	float currentTime;
};

struct ParticleForGPU {
	Matrix4x4 WVP;
	Matrix4x4 World;
	Vector4 color;
};

struct EmitterData {
	EulerTransform3D transform;	// エミッターのTransform
	uint32_t count;			// 発生数
	float frequency;		// 発生頻度
	float frequencyTime;	// 頻度用時刻
};