#pragma once

// C++
#include <cstdint>
#include <memory>

// MyHedder
#include "iScene/base/BaseScene.h"

#include "2d/sprite/Sprite.h"

class SampleScene :public BaseScene {
public:


public: // 公開メンバ関数
	// コンストラクタ
	SampleScene() = default;
	// デストラクタ
	~SampleScene() = default;
	// 初期化
	void Initialize()override;
	// 終了
	void Finalize()override;
	// 更新
	void Update()override;
	// 描画
	void Draw()override;

private: // 非公開メンバ関数

private: // 非公開メンバ変数
	std::unique_ptr<Sprite> sampleTexture_;
};

