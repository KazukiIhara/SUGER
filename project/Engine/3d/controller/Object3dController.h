#pragma once

// C++
#include <string>

// 数学関数ヘッダー
#include "math/function/MathFunction.h"

class Object3D;
class WorldTransform;
class Camera;

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

	// 削除フラグのセット
	void SetIsDelete(const bool& isDelete);

	// 親のセット
	void SetParent(WorldTransform* parent);

	// モデルのセット
	void SetModel(const std::string& filePath);

	// 有効フラグのセッター
	void SetIsActive(const bool& isActive);

	// ライトのオンオフ
	void SetEnableLightning(const bool& enableLightning);

	// スケールをゲット
	const Vector3& GetScale();
	// 回転のゲット
	const Vector3& GetRotate();
	// トランスレートをゲット
	const Vector3& GetTranslate();

	// 削除フラグをゲット
	bool GetIsDelete();

	// ワールドタンスフォームのゲット
	WorldTransform* GetWorldTransform();

	// カメラのゲット
	Camera* GetCamera();

private:
	// オブジェクトをセットする関数
	void SetObject(Object3D* object3d);
private:
	// コントロールする3Dオブジェクト
	Object3D* object3d_ = nullptr;
};