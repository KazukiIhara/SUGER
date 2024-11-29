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

}

void Line::Draw() {

}

void Line::AddLine() {

}

void Line::ClearLines() {
	
}

void Line::SetCamera(Camera* camera) {

}

void Line::SetIsActive(const bool& isActive) {

}

void Line::CreateInstancingResource() {

}

void Line::MapInstancingData() {

}
