#pragma once

// C++
#include <map>
#include <string>
#include <memory>

// MyHedder
#include "particle/3d/Particle3d.h"

class ParticleManager {
public:
	ParticleManager() = default;
	~ParticleManager() = default;

	// 初期化処理
	void Initialize();
	// 更新処理
	void Update();
	// 終了処理
	void Draw();
	// 終了処理
	void Finalize();

	// 板ポリパーティクル作成
	void Create(const WorldTransform& worldTransform, const std::string& name, const std::string& filePath);

private:
	// Particleデータコンテナ
	std::map <std::string, std::unique_ptr<Particle3D>> objects_;

};
