#include "SkiningEntity.h"

#include "framework/SUGER.h"

void SkiningEntity::Draw() {
	// PSOを設定
	SUGER::GetDirectXCommandList()->SetPipelineState(SUGER::GetPipelineState(kObject3d, blendMode_));
	// wvp用のCBufferの場所を設定
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
	// マテリアルCBufferの場所を設定
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	// ライトを転送
	punctualLight_->TransferLight();
	// カメラ情報を転送
	camera_->TransferCamera(3);
	// スキニング処理
	model_->Skinning();
	// モデル描画
	model_->Draw();

	// コライダーがあれば描画
	if (collider_) {
		collider_->Draw();
	}
}
