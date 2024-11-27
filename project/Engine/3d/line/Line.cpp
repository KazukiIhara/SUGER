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

	// マテリアルリソース作成
	CreateColorResource();
	// マテリアルデータ書き込み
	MapColorData();

	// srvのインデックスを割り当て
	srvIndex_ = SUGER::SrvAllocate();
	// Srvを作成
	SUGER::CreateSrvStructured(srvIndex_, instancingResource_.Get(), kNumMaxInstance, sizeof(LineData3D));
}

void Line::Update() {

}

void Line::Draw() {

}

void Line::AddLine() {

}

void Line::SetCamera(Camera* camera) {

}

void Line::SetIsActive(const bool& isActive) {

}

void Line::CreateInstancingResource() {

}

void Line::MapInstancingData() {

}

void Line::CreateColorResource() {

}

void Line::MapColorData() {

}
