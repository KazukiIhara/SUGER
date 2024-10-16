#pragma once

#include "3d/cameras/camera/Camera.h"

class RailCamera :public Camera {
public:
	RailCamera() = default;
	~RailCamera() = default;

	void Initialize()override;
	void Update()override;

private:

};
