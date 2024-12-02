#include "Line.h"
#include <cassert>

#include "framework/SUGER.h"

void Line::Initialize(Camera* camera) {
	// カメラがなければassert
	assert(camera);
	SetCamera(camera);

	// Instancingリソースを作る
	CreateInstancingResource();
	// Instancingデータを書き込む
	MapInstancingData();

	// srvのインデックスを割り当て
	srvIndex_ = SUGER::SrvAllocate();
	// Srvを作成
	SUGER::CreateSrvStructured(srvIndex_, instancingResource_.Get(), kNumMaxInstance, sizeof(LineData3D));
}

void Line::Update() {
	// 描画すべきインスタンス数
	instanceCount_ = static_cast<uint32_t>(lines_.size());

	if (instancingData_ != nullptr) {
		for (uint32_t i = 0; i < instanceCount_; ++i) {
			instancingData_[i] = lines_[i]; // CPU側のデータをGPU側に転送
		}
	}
}

void Line::Draw() {
	// コマンドリストを取得
	ID3D12GraphicsCommandList* commandList = SUGER::GetDirectXCommandList();
	// PSOを設定
	commandList->SetPipelineState(SUGER::GetPipelineState(kLine, blendMode_));
	// StructuredBufferのSRVを設定する
	commandList->SetGraphicsRootDescriptorTable(1, SUGER::GetSRVDescriptorHandleGPU(srvIndex_));
	// 描画！(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
	commandList->DrawInstanced(2, instanceCount_, 0, 0);
}

void Line::AddLine(const LineData3D& lineData3d) {
	// 最大数を超えていたら追加しない
	if (lines_.size() >= kNumMaxInstance) {
		return;
	}
	// 追加するLine
	LineData3D newLineData = lineData3d;
	// コンテナに挿入
	lines_.push_back(newLineData);
}

void Line::ClearLines() {
	lines_.clear();
}

void Line::SetCamera(Camera* camera) {
	assert(camera);
	camera_ = camera;
}

void Line::SetIsActive(const bool& isActive) {
	isActive_ = isActive;
}

void Line::CreateInstancingResource() {
	// instancing用のリソースを作る
	instancingResource_ = SUGER::CreateBufferResource(sizeof(LineData3D) * kNumMaxInstance);
}

void Line::MapInstancingData() {
	instancingData_ = nullptr;
	instancingResource_->Map(0, nullptr, reinterpret_cast<void**>(&instancingData_));

	for (uint32_t index = 0; index < kNumMaxInstance; ++index) {
		instancingData_[index].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}