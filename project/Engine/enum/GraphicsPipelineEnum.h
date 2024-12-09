#pragma once

	// ブレンドモード
	enum BlendMode {
		kBlendModeNone,
		kBlendModeNormal,
		kBlendModeAdd,
		kBlendModeSubtract,
		kBlendModeMultiply,
		kBlendModeScreen,
	};

	// パイプラインの種類
	enum GraphicsPipelineStateType {
		kObject2d,
		kObject3d,
		kObject3dSkinning,
		kParticle,
		kLine,
	};