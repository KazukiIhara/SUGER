#pragma once

// C++
#include <list>

#include "collider/Collider.h"
#include "objects/baseEntity/BaseEntity.h"

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
	// リセット
	void Reset();

	// コリジョンの当たり判定
	void CheckCollisionPair(Collider* colliderA, Collider* colliderB);
	// すべての当たり判定チェック
	void CheckAllCollisions();

	// コライダーの追加
	void AddCollider(BaseEntity* baseEntity);

private:
	// コライダー
	std::list<Collider*> colliders_;

};