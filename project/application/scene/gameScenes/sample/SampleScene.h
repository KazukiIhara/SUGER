#pragma once

// Common
#include "iScene/base/BaseScene.h"
#include "2d/controller/Object2dController.h"
#include "3d/entityController/EntityController.h"
#include "VFX/particle/emitterController/EmitterController.h"
#include "3d/lineController/LineController.h"

// SampleScene
#include "objects/pronamaChan/PronamaChan.h"
#include "objects/teapot/Teapot.h"

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
	void SceneStatePlayInitialize()override;
	// プレイフェーズ更新
	void SceneStatePlayUpdate()override;

private: // 非公開メンバ変数
	// エンティティコントローラ
	// プロ生ちゃん
	std::unique_ptr<PronamaChan> pronamaChan_ = nullptr;
	// ティーポット
	std::unique_ptr<Teapot> teapot_ = nullptr;

	std::unique_ptr<EntityController> terrain_ = nullptr;

	// Emitterコントローラ
	EmitterController emitter_;

	Vector3 scale_ = { 1.0f,1.0f,1.0f };

	Vector3	rotate_;

	Vector3	translate_ = { 0.0f,1.0f,0.0f };
};