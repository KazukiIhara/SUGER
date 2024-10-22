#pragma once

// C++
#include <string>

// 数学関数ヘッダー
#include "math/function/MathFunction.h"

class Sprite;

class Object2DController {
public:
	Object2DController() = default;
	~Object2DController() = default;

	// 初期化
	void Initialize(Sprite* object2d);

private:
	// オブジェクトのセット
	void SetObject(Sprite* object2d);

private:
	// コントロールするオブジェクト
	Sprite* object2d_ = nullptr;
};