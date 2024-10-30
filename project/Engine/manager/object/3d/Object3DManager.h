#pragma once

// C++
#include <map>
#include <string>
#include <memory>

// MyHedder
#include "3d/object/Object3d.h"

class ModelManager;
class PunctualLight;
class Camera;

class Object3DManager {
public:
	Object3DManager() = default;
	~Object3DManager() = default;

	// 初期化処理
	void Initialize(ModelManager* modelManager);
	// 更新処理
	void Update();
	// 描画処理
	void Draw();
	// スキニングモデル描画処理
	void DrawSkinning();
	// 終了処理
	void Finalize();

	// オブジェクト作成
	void Create(const std::string& name, const std::string& filePath, const EulerTransform3D& transform);

	// オブジェクト検索
	Object3D* Find(const std::string& name);

	void SetRequiredObjects(Camera* camera, PunctualLight* punctualLight);
	void SetSceneCamera(Camera* camera);

private:
	void SetModelManager(ModelManager* modelManager);
	void SetScenePunctualLight(PunctualLight* punctualLight);

private:
	// 3Dオブジェクトデータコンテナ
	std::map<std::string, std::unique_ptr<Object3D>> objects_;

private:
	// モデルマネージャのインスタンス
	ModelManager* modelManager_ = nullptr;
	// カメラのインスタンス
	Camera* camera_ = nullptr;
	// ライトのインスタンス
	PunctualLight* light_ = nullptr;

};