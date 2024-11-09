#pragma once

#include "3d/controller/Object3dController.h"
#include "worldTransform/WorldTransform.h"
#include "objects/baseEntity/BaseEntity.h"

class SampleEntity1:public BaseEntity {
public:
	SampleEntity1() = default;
	~SampleEntity1() = default;

	void Initialize()override;

	void Update()override;

	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision([[maybe_unused]] Collider* other)override;


private:

};