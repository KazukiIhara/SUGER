#pragma once

// MyHedder
#include "iScene/base/BaseScene.h"
#include "2d/controller/Object2dController.h"
#include "3d/entityController/EntityController.h"

#include "!FixEngine/emitterController/EmitterController.h"

class SampleScene:public BaseScene {
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
private: // 非公開メンバ変数
	// シーンのカメラ
	std::unique_ptr<Camera> sceneCamera_ = nullptr;
	// エンティティコントローラ
	EntityController entity_;
	// jeanne用のオブジェクト2Dコントローラ
	Object2DController pronama_chan;
	// Emitterコントローラ
	EmitterController emitter_;
};