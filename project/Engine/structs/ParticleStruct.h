#pragma once
#include "structs/ObjectStructs.h"

struct Particle {
	sTransform3D transform;
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

struct Emitter {
	sTransform3D transform;	// エミッターのTransform
	uint32_t count;			// 発生数
	float frequency;		// 発生頻度
	float frequencyTime;	// 頻度用時刻
};