#pragma once

// Common
#include "iScene/base/BaseScene.h"
#include "2d/controller/Object2dController.h"
#include "3d/entityController/EntityController.h"

#include "particle/emitterController/EmitterController.h"

// SampleScene
#include "objects/pronamaChan/PronamaChan.h"

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

	// プレイフェーズ初期化
	void SceneStatusPlayInitialize()override;
	// プレイフェーズ更新
	void SceneStatusPlayUpdate()override;

private: // 非公開メンバ変数
	// シーンのカメラ
	std::unique_ptr<Camera> sceneCamera_ = nullptr;
	// エンティティコントローラ
	PronamaChan pronamaChan_;
	// jeanne用のオブジェクト2Dコントローラ
	Object2DController pronamaChanTex;
	// Emitterコントローラ
	EmitterController emitter_;
};