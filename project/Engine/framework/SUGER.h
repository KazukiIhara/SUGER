#pragma once
// C++
#include <string>
#include <unordered_map>
#include <memory>

#include "d3d12.h"

#include "manager/window/WindowManager.h"
#include "input/direct/DirectInput.h"
#include "manager/directX/DirectXManager.h"
#include "manager/srv/SRVManager.h"
#include "manager/imgui/ImGuiManager.h"
#include "manager/texture/TextureManager.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"
#include "iScene/abstractFactory/AbstractSceneFactory.h"
#include "manager/model/ModelManager.h"
#include "manager/object/2d/Object2DManager.h"
#include "!FixEngine/emptyManager/EmptyManager.h"
#include "!FixEngine/entityManager/EntityManager.h"
#include "manager/particle/ParticleManager.h"
#include "manager/data/level/json/JsonLevelDataManager.h"
#include "2d/system/Object2dSystem.h"
#include "3d/system/Object3dSystem.h"
#include "particle/system/ParticleSystem.h"

#ifdef _DEBUG
#include "debugTools/leakChecker/d3dResource/D3DResourceLeakChecker.h"
#endif // _DEBUG


class WorldTransform;
class Sprite;
class Object3D;
class Model;
class RandomParticle;
class Camera;
class PunctualLight;
class JsonLevelData;


//
// new
//

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
	// キーを押している
	static bool PushKey(BYTE keyNumber);
	// キーを押した
	static bool TrrigerKey(BYTE keyNumber);
	// キーを押し続けている
	static bool HoldKey(BYTE keyNumber);
	// キーを離した
	static bool ReleaseKey(BYTE keyNumber);

	// ボタンを押している
	static bool PushButton(int controllerID, int buttonNumber);
	// ボタンを押した
	static bool TriggerButton(int controllerID, int buttonNumber);
	// ボタンを押し続けている
	static bool HoldButton(int controllerID, int buttonNumber);
	// ボタンを離した
	static bool ReleaseButton(int controllerID, int buttonNumber);

	// 左スティックのX軸位置を取得（-1000～1000の範囲にスケーリング）
	static int GetLeftStickX(int controllerID);
	// 左スティックのY軸位置を取得（-1000～1000の範囲にスケーリング）
	static int GetLeftStickY(int controllerID);

	// 右スティックのX軸位置を取得（-1000～1000の範囲にスケーリング）
	static int GetRightStickX(int controllerID);
	// 右スティックのY軸位置を取得（-1000～1000の範囲にスケーリング）
	static int GetRightStickY(int controllerID);

	// 方向キーの取得
	static bool IsPadUp(int controllerID);
	static bool IsPadRight(int controllerID);
	static bool IsPadDown(int controllerID);
	static bool IsPadLeft(int controllerID);

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
	static void CreateSrvStructured(uint32_t srvIndex, ID3D12Resource* pResource, uint32_t numElements, UINT structureByteStride);

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

#pragma region EmptyManager
	// エンプティの作成
	static std::string CreateEmpty(const std::string& name, const EulerTransform3D& transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} });
	// エンプティの更新
	static void UpdateEmpties();
	// エンプティの検索
	static Empty* FindEmpty(const std::string& name);
#pragma endregion

#pragma region EntityManager
	// エンティティの作成
	static std::string CreateEntity(const std::string& name, const std::string& filePath, const bool& haveSkiningAnimation = false, const EulerTransform3D& transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} });
	// エンティティの更新
	static void UpdateEntities();
	// エンティティの描画
	static void DrawEntiteis();
	// スキニング付きエンティティの描画
	static void DrawSkiningEntities();
	// エンティティ検索
	static Entity* FindEntity(const std::string& name);

	// シーンのカメラとライトをセット
	static void SetRequiredObjects(Camera* camera, PunctualLight* punctualLight);

	// シーンのカメラをセット
	static void SetSceneCamera(Camera* camera);
#pragma endregion

#pragma region ParticleManager
	// Particleの作成
	static void CreatePlaneParticle(const std::string& name, const std::string& filePath = "", const EulerTransform3D& transform = { {1.0f,1.0f,1.0f},{0.0f,0.0f,0.0f},{0.0f,0.0f,0.0f} });
	// Particleの更新
	static void UpdateParticle();
	// Particleの描画
	static void DrawParticle();

	// パーティクル検索
	static RandomParticle* FindParticle(const std::string& name);

#pragma endregion

#pragma region JsonLevelDataManager
	// JsonLevelDataManagerの機能
	// Json形式のlevelデータの読み込み
	static void LoadJsonLevelData(const std::string& fileName);
	// Json形式のLevelDataの検索
	static JsonLevelData* FindJsonLevelData(const std::string& levelDataName);
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
	// Skinningあり3dオブジェクト描画前処理
	static void PreDrawObject3DSkinning();

#pragma endregion

#pragma region ParticleSystem
	// ParticleSystemの機能
	// Particleの描画前処理
	static void PreDrawParticle3D();

#pragma endregion

#pragma region ImGuiDebug
	// FPSの表示
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
	static std::unique_ptr<EmptyManager> emptyManager_;
	static std::unique_ptr<EntityManager> entityManager_;
	static std::unique_ptr<ParticleManager> particleManager_;
	static std::unique_ptr<JsonLevelDataManager> jsonLevelDataManager_;
	static std::unique_ptr<Object2DSystem> object2dSystem_;
	static std::unique_ptr<Object3DSystem> object3dSystem_;
	static std::unique_ptr<ParticleSystem> particleSystem_;

};