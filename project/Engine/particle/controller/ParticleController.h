#pragma once

// C++
#include <string>

// 数学関数ヘッダー
#include "math/function/MathFunction.h"

class Particle3D;

// TODO:マネージャもコントローラも、パーティクルというよりはエミッターを制御しているので、一括で命名を変える

class ParticleController {
public:
	ParticleController() = default;
	~ParticleController() = default;

public:

	// 初期化
	void Initialize(Particle3D* particle3d);

	// 有効フラグのセッター
	void SetIsActive(const bool& isActive);

private:
	// パーティクルをセットする関数
	void SetParticle(Particle3D* particle3d);

private:
	// コントロールするパーティクル
	Particle3D* particle3d_ = nullptr;
};