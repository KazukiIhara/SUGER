#pragma once

#include "objects/baseEntity/BaseEntity.h"

class Baroon:public BaseEntity {
public:
	Baroon() = default;
	~Baroon() = default;

	void Initialize(const std::string& name, const std::string& filePath, const EulerTransform3D& transform);

	void Update();



private:

};