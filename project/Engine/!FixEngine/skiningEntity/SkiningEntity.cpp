#include "SkiningEntity.h"

#include "framework/SUGER.h"

void SkiningEntity::Draw() {
	// PSOを設定
	SUGER::GetDirectXCommandList()->SetPipelineState(SUGER::GetPipelineState(kObject3dSkinning, blendMode_));
	// wvp用のCBufferの場所を設定
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
	// ライトを転送
	punctualLight_->TransferLight();
	// カメラ情報を転送
	camera_->TransferCamera();
	// スキニング付きモデル描画
	model_->DrawSkinning();
}