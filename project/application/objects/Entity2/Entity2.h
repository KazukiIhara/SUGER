#pragma once

#include "3d/controller/Object3dController.h"
#include "worldTransform/WorldTransform.h"
#include "collider/Collider.h"

class Entity2:public Collider {
public:
	Entity2() = default;
	~Entity2() = default;

	void Initialize();

	void Update();

private:

};
