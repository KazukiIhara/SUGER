#pragma once

#include "!FixEngine/entity/Entity.h"

class SkiningEntity :public Entity {
public:
	SkiningEntity() = default;
	~SkiningEntity() = default;

	// 描画
	void Draw()override;

};