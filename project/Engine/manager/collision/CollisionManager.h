#pragma once

// C++
#include <list>
#include <string>

#include "3d/entityController/EntityController.h"

class CollisionManager {
public:
	CollisionManager() = default;
	~CollisionManager() = default;

	// 初期化
	void Initialize();
	// 更新
	void Update();
	// 終了
	void Finalize();
	// コライダー追加
	void AddCollider(EntityController* controller);
	// コンテナをクリア
	void ClearContainer();
	// ペア同士の当たり判定をチェック
	void CheckCollisionPair(EntityController* controllerA, EntityController* controllerB);
	// すべてのコライダー同士の当たり判定チェック
	void CheckAllCollisions();

private:
	// コントローラコンテナ
	std::list<EntityController*> controllers_;
};