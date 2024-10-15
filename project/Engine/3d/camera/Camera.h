#pragma once
// C++
#include <memory>

// DirectX
#include <d3d12.h>

// MyHedder
#include "directX/includes/ComPtr.h"
#include "worldTransform/WorldTransform.h"
#include "structs/CameraStruct.h"

class Camera {
public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	void CreateCameraResource();
	void MapCameraData();

	void UpdateCameraData();

	void TransferCamera();

	// カメラのTranslateをセット
	void SetTranslate(const Vector3& translate);
	// カメラのrotateをセット
	void SetRotate(const Vector3& rotate);

	// ビュープロジェクションマトリックスを送る関数
	Matrix4x4 GetViewProjectionMatrix()const {
		return viewProjectionMatrix_;
	}
	// ワールド行列を送る関数
	Matrix4x4 GetWorldMatrix()const {
		return worldMatrix_;
	}
	// ワールド座標を送る関数
	Vector3 GetWorldPos()const {
		return worldPos_;
	}

private:
	// カメラのトランスフォームを受け取る箱
	WorldTransform transform_{};
	// カメラのワールドマトリックス
	Matrix4x4 worldMatrix_{};
	// カメラのワールドポジション
	Vector3 worldPos_{};
	// ビュープロジェクションマトリックス
	Matrix4x4 viewProjectionMatrix_{};
	// 水平方向視野角
	float fovY_ = 0.45f;
	// アスペクト比
	float aspectRaito_ = 16.0f / 9.0f;
	// ニアクリップ距離
	float nearClipRange_ = 0.1f;
	// ファークリップ距離
	float farClipRange_ = 100.0f;

	// Camera用リソース
	ComPtr<ID3D12Resource> cameraResource_ = nullptr;
	// Camera用データ
	sCameraForGPU* cameraData_ = nullptr;

};
