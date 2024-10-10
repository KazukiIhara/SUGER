#pragma once
#pragma once
#include "math/function/MathFunction.h"

// DirectX
#include <d3d12.h>

// MyHedder
#include "framework/SUGER.h"
#include "structs/PunctualLightStruct.h"
#include "directX/includes/ComPtr.h"

class cPunctualLight {
public: // 構造体
	// シェーダーに送るカメラ座標
	struct sCameraForGPU {
		Vector3 worldPosition;
		float padding;
	};

public: // メンバ関数
	// 初期化
	void Initialize();
	void Update();
	void TransferLight();

	void SetPunctualLightSetting(const PunctualLightData& punctualLightSetting);
	void SetCameraPosition(const Vector3& cameraPosition);

private: // 非公開メンバ関数
#pragma region Light
	void CreatePunctualLightResource();
	void MapPunctualLightData();
#pragma endregion	

#pragma region Camera
	void CreateCameraResource();
	void MapCameraData();
#pragma endregion

	void UpdateDirectionalLight();
	void UpdatePointLight();
	void UpdateSpotLight();

	void UpdateCamera();

private: // メンバ変数
	// PunctualLight用のリソース
	Microsoft::WRL::ComPtr<ID3D12Resource> punctualLightResource_ = nullptr;
	// シェーダーに送るライトのデータ
	PunctualLightData* punctualLightData_ = nullptr;
	// PunctualLight
	PunctualLightData punctualLight{};

	// Camera用リソース
	Microsoft::WRL::ComPtr<ID3D12Resource> cameraResource_ = nullptr;
	// Camera用データ
	sCameraForGPU* cameraData_ = nullptr;
	// カメラを受け取る箱
	sCameraForGPU camera;

};
