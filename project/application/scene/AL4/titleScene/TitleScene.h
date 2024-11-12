#pragma once

// C++
#include <cstdint>
#include <memory>
#include <array>

// MyHedder
#include "iScene/base/BaseScene.h"

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

};