#pragma once

#include "directX/includes/ComPtr.h"
#include "!FixEngine/empty/empty.h"
#include "3d/model/Model.h"
#include "3d/cameras/camera/Camera.h"
#include "3d/lights/punctualLight/PunctualLight.h"

#include "enum/GraphicsPipelineEnum.h"


class Entity :public Empty {
public:
	Entity() = default;
	~Entity() = default;

	// 初期化
	void Initialize()override;
	// 更新
	void Update()override;
	// 描画
	void Draw();

	// カメラのゲット
	Camera* GetCamera();

	// カメラのセット
	void SetCamera(Camera* camera);
	// ライトのセット
	void SetLight(PunctualLight* punctualLight);
private:
	// WVP用のリソース作成
	void CreateWVPResource();
	// データを書き込む
	void MapWVPData();
private:
	// モデルを受け取る箱
	Model* model_ = nullptr;

	// ブレンドモード
	BlendMode blendMode_ = kBlendModeNormal;

	// WVP用のリソース
	ComPtr<ID3D12Resource> transformationResource_ = nullptr;
	// シェーダーに送るWVPデータ
	TransformationMatrix* transformationData_ = nullptr;

	// カメラを受け取る箱
	Camera* camera_ = nullptr;
	// ライトを受け取る箱
	PunctualLight* punctualLight_ = nullptr;

};
