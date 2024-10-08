#pragma once
// C++
#include <string>
#include <unordered_map>
#include <memory>

#include "d3d12.h"

#include "directX/includes/ComPtr.h"
#include "externals/DirectXTex/DirectXTex.h"

#include "structs/TextureStruct.h"
#include "enum/GraphicsPipelineEnum.h"

class D3DResourceLeakChecker;
class WindowManager;
class DirectInput;
class DirectXManager;
class SRVManager;
class ImGuiManager;
class TextureManager;
class GraphicsPipelineManager;
class Object2DSystem;
class AbstractSceneFactory;


class SUGER {
public:
	// 仮想デストラクタ
	virtual~SUGER() = default;
	// 初期化
	virtual void Initialize();
	// 終了
	virtual void Finalize();
	// 更新
	virtual void Update();
	// 描画
	virtual void Draw() = 0;
	// 終了チェック
	virtual bool IsEndRequest() {
		return endRequest_;
	}
public: // 公開メンバ関数
	// 実行
	void Run();
	// 描画前処理
	void PreDraw();
	// 描画後処理
	void PostDraw();
public: // クラスメソッド

#pragma region WindowManager
	// WindowManagerの機能
#pragma endregion

#pragma region DirectInput
	// DirectInputの機能
#pragma endregion

#pragma region DirectXManager
	// DirectXManagerの機能
	// デバイス取得
	static ID3D12Device* GetDirectXDevice();
	// コマンドリスト取得関数
	static ID3D12GraphicsCommandList* GetDirectXCommandList();
#pragma endregion

#pragma region SRVManager
	// SRVManagerの機能
	// ディスクリプターテーブルのセット
	static void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t srvIndex);

#pragma endregion

#pragma region ImGuiManager
	// ImGuiManagerの機能
#pragma endregion

#pragma region TextureManager
	// TextureManagerの機能
	// 画像読み込み関数
	static void LoadTexture(const std::string& filePath);
	// 画像取得関数
	static std::unordered_map<std::string, Texture>& GetTexture();
	// メタデータ取得
	static const DirectX::TexMetadata& GetTextureMetaData(const std::string& filePath);

#pragma endregion

#pragma region GraphicsPipelineManager
	// GraphicsPipelineManagerの機能
	// パイプライン取得関数
	static ID3D12PipelineState* GetPipelineState(PipelineState pipelineState, BlendMode blendMode);

#pragma endregion

#pragma region Object2DSystem
	// Object2DSystemの機能
	// 2dオブジェクト描画前処理
	static void PreDrawObject2D();
#pragma endregion


private: // メンバ変数
	// 終了リクエスト
	bool endRequest_ = false;
private: // クラスのポインタ
	static std::unique_ptr<D3DResourceLeakChecker> leakCheck_;
	static std::unique_ptr<WindowManager> windowManager_;
	static std::unique_ptr<DirectInput> directInput_;
	static std::unique_ptr<DirectXManager> directXManager_;
	static std::unique_ptr<SRVManager> srvManager_;
	static std::unique_ptr<ImGuiManager> imguiManager_;
	static std::unique_ptr<TextureManager> textureManager_;
	static std::unique_ptr<GraphicsPipelineManager> graphicsPipelineManager_;
	static std::unique_ptr<Object2DSystem> object2dSystem_;
};