#pragma once

// C++
#include <cstdint>
#include <memory>
#include <array>

// MyHedder
#include "iScene/base/BaseScene.h"
#include "structs/ObjectStructs.h"
#include "3d/cameras/railCamera/RailCamera.h"

class ShootingCoasterScene :public BaseScene {
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
	// レールカメラ
	std::unique_ptr<RailCamera> railCamera_ = nullptr;
	// レールの最大数
	static const uint32_t kRailNum_ = 5;
	// レールのトランスフォーム
	std::array<Transform3D, kRailNum_> railTransform_{};

};

