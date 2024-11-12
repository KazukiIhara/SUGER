#pragma once

// C++
#include <cstdint>
#include <memory>
#include <array>

// MyHedder
#include "iScene/base/BaseScene.h"

#include "2d/controller/Object2dController.h"

class TitleScene:public BaseScene {
public:
	TitleScene() = default;
	~TitleScene() = default;

	// 初期化
	void Initialize()override;
	// 終了
	void Finalize()override;
	// 更新
	void Update()override;
private:

	Object2DController pushA_;

};