#pragma once
// C++
#include <string>
#include <unordered_map>
#include <memory>

#include "d3d12.h"

#include "directX/includes/ComPtr.h"
#include "externals/DirectXTex/DirectXTex.h"

#include "structs/ObjectStructs.h"
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
class ModelManager;
class Object2DManager;
class Object3DManager;
class ParticleManager;
class Object2DSystem;
class Object3DSystem;
class ParticleSystem;
class AbstractSceneFactory;

class WorldTransform;
class Sprite;
class Object3D;
class Model;
class Camera;
class PunctualLight;

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
	virtual void Draw();
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
	// バッファリソースの作成
	static ComPtr<ID3D12Resource> CreateBufferResource(size_t sizeInBytes);
#pragma endregion

#pragma region SRVManager
	// SRVManagerの機能
	// CPUの特定のインデックスハンドルを取得
	static D3D12_CPU_DESCRIPTOR_HANDLE GetSRVDescriptorHandleCPU(uint32_t index);
	// GPUの特定のインデックスハンドルを取得
	static D3D12_GPU_DESCRIPTOR_HANDLE GetSRVDescriptorHandleGPU(uint32_t index);

	// ディスクリプターテーブルのセット
	static void SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t srvIndex);
	// Allocate
	static uint32_t SrvAllocate();
	// instancing用のsrv作成
	static void CreateSrvInstancing(uint32_t srvIndex, ID3D12Resource* pResource, uint32_t numElements, UINT structureByteStride);

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

#pragma region ModelManager
	// モデルの読み込み
	static void LoadModel(const std::string& filePath);
	// 球体の作成
	static void CreateSphere(const std::string& textureFilePath);
	// モデルの検索
	static Model* FindModel(const std::string& filePath);
#pragma endregion

#pragma region Object2DManager
	// 2Dオブジェクトの作成
	static void Create2DObject(const std::string& name, const std::string& filePath);
	// 2Dオブジェクトの更新
	static void Update2DObjects();
	// 2Dオブジェクトの描画
	static void Draw2DObjects();

	// 2Dオブジェクト検索
	static Sprite* FindObject2D(const std::string& name);
#pragma endregion

#pragma region Object3DManager
	// 3Dオブジェクトの作成
	static void Create3DObject(const std::string& name, const std::string& filePath = "", const Transform3D& transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} });
	// 3Dオブジェクトの更新
	static void Update3DObjects();
	// 3Dオブジェクトの描画
	static void Draw3DObjects();

	// 3Dオブジェクト検索
	static Object3D* FindObject3D(const std::string& name);

	// シーンのカメラとライトをセット
	static void SetRequiredObjects(Camera* camera, PunctualLight* punctualLight);

	// シーンのカメラをセット
	static void SetSceneCamera(Camera* camera);
#pragma endregion

#pragma region ParticleManager
	// Particleの作成
	static void CreatePlaneParticle(const std::string& name, const std::string& filePath = "", const Transform3D& transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} });
	// Particleの更新
	static void UpdateParticle();
	// Particleの描画
	static void DrawParticle();

#pragma endregion

#pragma region Object2DSystem
	// Object2DSystemの機能
	// 2dオブジェクト描画前処理
	static void PreDrawObject2D();
#pragma endregion

#pragma region Object3DSystem
	// Object3DSystemの機能
	// 3dオブジェクト描画前処理
	static void PreDrawObject3D();
#pragma endregion

#pragma region ParticleSystem
	// ParticleSystemの機能
	// Particleの描画前処理
	static void PreDrawParticle3D();

#pragma endregion

#pragma region ImGuiDebug
	void ShowFPS();
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
	static std::unique_ptr<ModelManager> modelManager_;
	static std::unique_ptr<Object2DManager> object2dManager_;
	static std::unique_ptr<Object3DManager> object3dManager_;
	static std::unique_ptr<ParticleManager> particleManager_;
	static std::unique_ptr<Object2DSystem> object2dSystem_;
	static std::unique_ptr<Object3DSystem> object3dSystem_;
	static std::unique_ptr<ParticleSystem> particleSystem_;
};