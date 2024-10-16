#include "Object3d.h"

#include "framework/SUGER.h"

void Object3D::Initialize() {
	// wvp用のリソース作成
	CreateWVPResource();
	// データを書き込む
	MapWVPData();
}

void Object3D::Update() {
	// モデル読み込み済みなら更新
	if (model) {
		model->Update();
	}

	// WVPマトリックスを作る
	transform_.Update();
	transformationData_->World = transform_.worldMatrix_;
	transformationData_->ViewProjection = camera_->GetViewProjectionMatrix();
	transformationData_->WorldInverseTransepose = MakeInverseTransposeMatrix(transform_.worldMatrix_);
}

void Object3D::Draw(BlendMode blendMode) {
	// PSOを設定
	SUGER::GetDirectXCommandList()->SetPipelineState(SUGER::GetPipelineState(kObject3d, blendMode));
	// wvp用のCBufferの場所を設定
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
	// ライトを転送
	punctualLight_->TransferLight();
	// カメラ情報を転送
	camera_->TransferCamera();
	// 3Dモデルが割り当てられていれば描画する
	if (model) {
		model->Draw();
	}
}

void Object3D::CreateWVPResource() {
	// WVP用のリソースを作る
	transformationResource_ = SUGER::CreateBufferResource(sizeof(sTransformationMatrix));
}

void Object3D::MapWVPData() {	// データを書き込む
	transformationData_ = nullptr;
	// 書き込むためのアドレスを取得
	transformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&transformationData_));
	// 単位行列を書き込んでおく
	transformationData_->World = MakeIdentityMatrix4x4();
	transformationData_->ViewProjection = MakeIdentityMatrix4x4();
	transformationData_->WorldInverseTransepose = MakeIdentityMatrix4x4();
}

void Object3D::SetModel(const std::string& filePath) {
	objectname_ = filePath;
	model = SUGER::FindModel(filePath);
}
