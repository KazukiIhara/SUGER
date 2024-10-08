#pragma once

// MyHedder
#include "framework/SUGER.h"

// 前方宣言
class SceneFactory;
class SceneManager;

// ゲームクラス
class MyGame :public SUGER {
public: // 公開メンバ関数
	MyGame() = default;
	~MyGame() = default;

	// 初期化
	void Initialize()override;
	// 終了
	void Finalize()override;
	// 更新
	void Update()override;
	// 描画
	void Draw()override;

private: // メンバ変数
	// シーンファクトリ
	SceneFactory* sceneFactory_ = nullptr;
	// シーンマネージャ
	SceneManager* sceneManager_ = nullptr;
};
