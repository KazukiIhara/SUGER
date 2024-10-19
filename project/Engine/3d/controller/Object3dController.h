#pragma once

class Object3D;

class Object3DController {
public:
	Object3DController() = default;
	~Object3DController() = default;

	void Initialize(Object3D* object3d);

	void SetTranslate(const Vector3& translate);

private:
	// オブジェクトをセットする関数
	void SetObject3D(Object3D* object3d);

	// コントロールする3Dオブジェクト
	Object3D* object3d_ = nullptr;
};