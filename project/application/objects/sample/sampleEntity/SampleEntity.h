#pragma once

#include "3d/controller/Object3dController.h"
#include "worldTransform/WorldTransform.h"
#include "objects/baseEntity/BaseEntity.h"

class SampleEntity:public BaseEntity {
public:
	SampleEntity() = default;
	~SampleEntity() = default;

	void Initialize();

	void Update();

	// 衝突を検知したら呼び出されるコールバック関数
	void OnCollision([[maybe_unused]] Collider* other)override;


private:


};