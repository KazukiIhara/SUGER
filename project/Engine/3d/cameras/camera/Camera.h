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
	virtual void Initialize();

	// 更新
	virtual void Update();

	// 定数バッファに転送
	void TransferCamera();

	// translateのゲッター
	Vector3 GetTranslate()const;
	// rotateのゲッター
	Vector3 GetRotate()const;

	// カメラのTranslateをセット
	void SetTranslate(const Vector3& translate);
	// カメラのrotateをセット
	void SetRotate(const Vector3& rotate);

	// ワールドトランスフォームを送る
	WorldTransform* GetWorldTransformPtr();

	// ビュープロジェクションマトリックスを送る関数
	Matrix4x4 GetViewProjectionMatrix()const {
		return viewProjectionMatrix_;
	}
	// ワールド行列を送る関数
	Matrix4x4 GetWorldMatrix()const {
		return transform_.worldMatrix_;
	}
	// ワールド座標を送る関数
	Vector3 GetWorldPos()const {
		return worldPos_;
	}

private:

	// カメラのリソースを作成
	void CreateCameraResource();
	// カメラのデータを入力
	void MapCameraData();
	// カメラのデータを更新
	void UpdateCameraData();

protected:
	// カメラのトランスフォームを受け取る箱
	WorldTransform transform_{};
	// カメラのワールドポジション
	Vector3 worldPos_{};
	// ビュープロジェクションマトリックス
	Matrix4x4 viewProjectionMatrix_{};
	// 水平視野角(度数法)
	float fovYDegrees_ = 60.0f;
	// 水平方向視野角
	float fovY_ = fovYDegrees_ * (std::numbers::pi_v<float> / 180.0f);
	// アスペクト比
	float aspectRaito_ = 16.0f / 9.0f;
	// ニアクリップ距離
	float nearClipRange_ = 0.1f;
	// ファークリップ距離
	float farClipRange_ = 1000.0f;

	// カメラの初期トランスフォーム
	const Vector3 kDefaultCameraRotate_ = { 0.45f,0.0f,0.0f };
	const Vector3 kDefaultCameraTranslate_ = { 0.0f,2.0f,-5.0f };

	// Camera用リソース
	ComPtr<ID3D12Resource> cameraResource_ = nullptr;
	// Camera用データ
	CameraForGPU* cameraData_ = nullptr;

};
