#include "empty.h"

void Empty::Initialize() {
	// 有効化
	isActive_ = true;
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
}

void Empty::Update() {
	// ワールドトランスフォームの更新
	worldTransform_.Update();
}

void Empty::SetIsActive(const bool& isActive) {
	isActive_ = isActive;
}

void Empty::SetIsDelete(const bool& isDelete) {
	isDelete_ = isDelete;
}

bool Empty::GetIsActive() const {
	return isActive_;
}

bool Empty::GetIsDelete() const {
	return isDelete_;
}
