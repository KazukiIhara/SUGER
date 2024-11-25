#pragma once

#include "3d/entityController/EntityController.h"

class PronamaChan : public EntityController {
public:
	PronamaChan() = default;
	~PronamaChan() = default;

	// 衝突コールバック関数
	void OnCollision([[maybe_unused]] Collider* other);

};