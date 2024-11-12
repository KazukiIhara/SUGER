#pragma once

#include "objects/baseEntity/BaseEntity.h"

class Baroon:public BaseEntity {
public:
	Baroon() = default;
	~Baroon() = default;

	void Initialize(const std::string& name, const std::string& filePath, const EulerTransform3D& transform);

	void Update();

	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision([[maybe_unused]] Collider* other)override;

	bool GetIsDead() {
		return isDelete_;
	}

private:
	bool isDelete_ = false;
};