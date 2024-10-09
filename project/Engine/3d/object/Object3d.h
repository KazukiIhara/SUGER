#pragma once

// C++
#include <memory>
#include <string>

// DirectX
#include <d3d12.h>

#include "directX/includes/ComPtr.h"
#include "structs/ObjectStructs.h"
#include "structs/ModelStructs.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"
#include "3d/model/Model.h"
#include "worldTransform/WorldTransform.h"


class Object3D {
public:
	Object3D() = default;
	~Object3D() = default;
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw(BlendMode blendMode = kBlendModeNormal);

private:
	/*wvp用のリソース作成*/
	void CreateWVPResource();
	/*データを書き込む*/
	void MapWVPData();
public: // Setter
	// modelのセット
	void SetModel(const std::string& filePath);
	// 拡縮のセット
	void SetScale(const Vector3& scale) {
		this->transform_.scale = scale;
	}
	// 回転のセット
	void SetRotate(const Vector3& rotate) {
		this->transform_.rotate = rotate;
	}
	// 移動量のセット
	void SetTranslate(const Vector3& translate) {
		this->transform_.translate = translate;
	}
	// トランスフォームのセット
	void SetTransform(const WorldTransform& transform) {
		this->transform_.scale = transform.scale;
		this->transform_.rotate = transform.rotate;
		this->transform_.translate = transform.translate;
	}
	// ライトのセット
	void SetPunctualLight(PunctualLight* punctualLight) {
		punctualLight_ = punctualLight;
	}
public: // Getter
	// 拡縮のゲッター
	const Vector3& GetScale() const {
		return transform_.scale;
	}
	// 回転のゲッター
	const Vector3& GetRotate() const {
		return transform_.rotate;
	}
	// 移動量のゲッター
	const Vector3& GetTranslate() const {
		return transform_.translate;
	}
	// オブジェクトの名前のゲッター
	const std::string& GetName()const {
		return objectname_;
	}
	Model* GetModel() {
		return model;
	}

private:/*メンバ変数*/

	// モデルを受け取る箱
	Model* model = nullptr;

	/*WVP用のリソース*/
	ComPtr<ID3D12Resource> transformationResource_ = nullptr;
	// シェーダーに送るトランスフォームデータ
	sTransformationMatrix* transformationData_ = nullptr;
	/*トランスフォーム*/
	WorldTransform transform_;

	/*ビュープロジェクションを受け取る箱*/
	Matrix4x4* viewProjection_ = nullptr;

	// ライトを受け取る箱
	PunctualLight* punctualLight_ = nullptr;

	// オブジェクトの名前
	std::string objectname_{};

};
