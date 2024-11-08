#pragma once

#include "3d/controller/Object3dController.h"
#include "worldTransform/WorldTransform.h"
#include "collider/Collider.h"

class Entity1:public Collider {
public:
	Entity1() = default;
	~Entity1() = default;

	void Initialize();

	void Update();

private:

};