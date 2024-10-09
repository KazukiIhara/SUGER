#pragma once

// C++
#include <memory>
#include <string>

// DirectX
#include <d3d12.h>

#include "directX/includes/ComPtr.h"
#include "structs/ObjectStructs.h"
#include "structs/ModelStructs.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"
#include "3d/model/Model.h"


class Object3D {
public:
	Object3D() = default;
	~Object3D() = default;
	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 描画
	void Draw(BlendMode blendMode = kBlendModeNormal);

private:
	/*wvp用のリソース作成*/
	void CreateWVPResource();
	/*データを書き込む*/
	void MapWVPData();

};
