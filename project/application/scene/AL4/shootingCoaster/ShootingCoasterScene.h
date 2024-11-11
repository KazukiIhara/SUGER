#pragma once

// C++
#include <cstdint>
#include <memory>
#include <array>

// MyHedder
#include "iScene/base/BaseScene.h"
#include "structs/ObjectStructs.h"
#include "3d/cameras/railCamera/RailCamera.h"
#include "importer/level/json/JsonLevelDataImporter.h"

// Objects
#include "objects/player/Player.h"
#include "objects/baroon/Baroon.h"

class ShootingCoasterScene:public BaseScene {
public: // 公開メンバ関数
	// コンストラクタ
	ShootingCoasterScene() = default;
	// デストラクタ
	~ShootingCoasterScene() = default;
	// 初期化
	void Initialize()override;
	// 終了
	void Finalize()override;
	// 更新
	void Update()override;
private: // 非公開メンバ変数
	// jsonデータインポーター
	JsonLevelDataImporter jsonImporter_;

	// レールカメラ
	std::unique_ptr<RailCamera> railCamera_ = nullptr;

	// プレイヤー
	std::unique_ptr<Player> player_ = nullptr;

	// 風船
	std::list<std::unique_ptr<Baroon>> baroons_;

};

