#pragma once

// 数学関数ヘッダー
#include "math/function/MathFunction.h"

class Object3D;

class Object3DController {
public:
	Object3DController() = default;
	~Object3DController() = default;

	// 初期化
	void Initialize(Object3D* object3d);

	// スケールのセット
	void SetScale(const Vector3& scale);
	// 回転のセット
	void SetRotate(const Vector3& rotate);
	// トランスレートのセット
	void SetTranslate(const Vector3& translate);


private:
	// オブジェクトをセットする関数
	void SetObject3D(Object3D* object3d);

	// コントロールする3Dオブジェクト
	Object3D* object3d_ = nullptr;
};