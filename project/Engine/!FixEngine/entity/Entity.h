#pragma once

#include "directX/includes/ComPtr.h"
#include "!FixEngine/empty/empty.h"
#include "3d/model/Model.h"
#include "3d/cameras/camera/Camera.h"
#include "3d/lights/punctualLight/PunctualLight.h"


class Entity :public Empty {
public:
	Entity() = default;
	~Entity() = default;

	// 初期化
	void Initialize()override;
	// 更新
	void Update()override;

private:
	// モデルを受け取る箱
	Model* model_ = nullptr;

	// WVP用のリソース
	ComPtr<ID3D12Resource> transformationResource_ = nullptr;
	// シェーダーに送るWVPデータ
	TransformationMatrix* transformationData_ = nullptr;
	// カメラを受け取る箱
	Camera* camera_ = nullptr;
	// ライトを受け取る箱
	PunctualLight* punctualLight_ = nullptr;

};
