#pragma once

// C++
#include <string>

// 数学関数ヘッダー
#include "math/function/MathFunction.h"

class RandomParticle;

// TODO:マネージャもコントローラも、パーティクルというよりはエミッターを制御しているので、一括で命名を変える

class ParticleController {
public:
	ParticleController() = default;
	~ParticleController() = default;

public:

	// 初期化
	void Initialize(RandomParticle* particle3d);

	// 回転のセット
	void SetRotate(const Vector3& rotate);

	// 移動量のセット
	void SetTranslate(const Vector3& translate);

	// 有効フラグのセッター
	void SetIsActive(const bool& isActive);

private:
	// パーティクルをセットする関数
	void SetParticle(RandomParticle* particle3d);

private:
	// コントロールするパーティクル
	RandomParticle* particle3d_ = nullptr;
};