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

void Empty::SetName(const std::string& name) {
	name_ = name;
}

void Empty::SetScale(const Vector3& scale) {
	worldTransform_.scale_ = scale;
}

void Empty::SetRotate(const Vector3& rotate) {
	worldTransform_.rotate_ = rotate;
}

void Empty::SetTranslate(const Vector3& translate) {
	worldTransform_.translate_ = translate;
}

void Empty::SetTransform(const EulerTransform3D& transform) {
	worldTransform_.scale_ = transform.scale;
	worldTransform_.rotate_ = transform.rotate;
	worldTransform_.translate_ = transform.translate;
}

void Empty::SetIsActive(const bool& isActive) {
	isActive_ = isActive;
}

void Empty::SetIsDelete(const bool& isDelete) {
	isDelete_ = isDelete;
}

std::string Empty::GetName() const {
	return name_;
}

bool Empty::GetIsActive() const {
	return isActive_;
}

bool Empty::GetIsDelete() const {
	return isDelete_;
}
