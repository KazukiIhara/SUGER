#include "Entity.h"

#include "framework/SUGER.h"

void Entity::Initialize() {
	// 基底クラスの初期化処理
	Empty::Initialize();
	// WVP用のリソース作成

}

void Entity::Update() {
	// モデルの更新
	model_->Update();
	// 基底クラスの更新処理
	Empty::Update();
	// WVPマトリックス作成
	transformationData_->World = worldTransform_.worldMatrix_;
	transformationData_->ViewProjection = camera_->GetViewProjectionMatrix();
	transformationData_->WorldInverseTransepose = MakeInverseTransposeMatrix(worldTransform_.worldMatrix_);
}

void Entity::Draw() {
	// PSOを設定
	SUGER::GetDirectXCommandList()->SetPipelineState(SUGER::GetPipelineState(kObject3d, blendMode_));
	// wvp用のCBufferの場所を設定
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
	// ライトを転送
	punctualLight_->TransferLight();
	// カメラ情報を転送
	camera_->TransferCamera();
	// 3Dモデル描画
	model_->Draw();
}

Camera* Entity::GetCamera() {
	return camera_;
}

void Entity::SetCamera(Camera* camera) {
	camera_ = camera;
}

void Entity::SetLight(PunctualLight* punctualLight) {
	punctualLight_ = punctualLight;
}

void Entity::CreateWVPResource() {
	// WVP用のリソースを作る
	transformationResource_ = SUGER::CreateBufferResource(sizeof(TransformationMatrix));
}

void Entity::MapWVPData() {
	// データを書き込む
	transformationData_ = nullptr;
	// 書き込むためのアドレスを取得
	transformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationData_));
	// 単位行列を書き込んでおく
	transformationData_->World = MakeIdentityMatrix4x4();
	transformationData_->ViewProjection = MakeIdentityMatrix4x4();
	transformationData_->WorldInverseTransepose = MakeIdentityMatrix4x4();
}
