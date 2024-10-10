#pragma once

// C++
#include <cstdint>
#include <memory>

// MyHedder
#include "iScene/base/BaseScene.h"

#include "2d/sprite/Sprite.h"
#include "3d/camera/Camera.h"
#include "3d/lights/punctualLight/PunctualLight.h"
#include "3d/object/Object3d.h"

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
	// 描画
	void Draw()override;
private: // 非公開メンバ変数
	std::unique_ptr<Sprite> sampleTexture_;

	std::unique_ptr<Camera> camera_;
	WorldTransform cameraTransform_{};

	std::unique_ptr<PunctualLight> light_;

	std::unique_ptr<Object3D> sampleObject_;
};

