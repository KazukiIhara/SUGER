#pragma once

// C++
#include <map>
#include <string>
#include <memory>

// MyHedder
#include "particle/3d/Particle3d.h"

class ModelManager;
class TextureManager;
class Camera;

class ParticleManager {
public:
	ParticleManager() = default;
	~ParticleManager() = default;

	// 初期化処理
	void Initialize(ModelManager* modelManager,TextureManager* textureManager);
	// 更新処理
	void Update();
	// 終了処理
	void Draw();
	// 終了処理
	void Finalize();

	// 作成済みのパーティクル検索
	Particle3D* Find(const std::string& name);

	// 板ポリパーティクル作成
	void CreatePlane(const std::string& name, const std::string& filePath, const Transform3D& transform);

	// ModelManagerのセット
	void SetModelManager(ModelManager* modelManager);
	// TextureManagerのセット
	void SetTextureManager(TextureManager* textureManager);
	// Cameraのセット
	void SetSceneCamera(Camera* camera);
private:
	// Particleデータコンテナ
	std::map <std::string, std::unique_ptr<Particle3D>> objects_;

private:
	// モデルマネージャのインスタンス
	ModelManager* modelManager_ = nullptr;
	// テクスチャマネージャのインスタンス
	TextureManager* textureManager_ = nullptr;
	// カメラのインスタンス
	Camera* camera_ = nullptr;

};
