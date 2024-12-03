#include "CollisionManager.h"

void CollisionManager::Initialize() {
	// コンテナをクリア
	ClearContainer();
}

void CollisionManager::Update() {
	// リスト内のすべての当たり判定を取得
	CheckAllCollisions();
}

void CollisionManager::Finalize() {
	// コンテナをクリア
	ClearContainer();
}

void CollisionManager::AddCollider(EntityController* controller) {
	// コンテナに追加
	controllers_.push_back(controller);
}

void CollisionManager::ClearContainer() {
	// コンテナをクリア
	controllers_.clear();
}

void CollisionManager::CheckCollisionPair(EntityController* controllerA, EntityController* controllerB) {
	// A,Bのコライダーを取得
	Collider* colliderA = controllerA->GetCollider();
	Collider* colliderB = controllerB->GetCollider();

	// A,Bの座標を取得
	Vector3 positionA = colliderA->GetWorldPosition();
	Vector3 positionB = colliderB->GetWorldPosition();
	// 座標の差分ベクトル
	Vector3 subtract = positionB - positionA;
	// 座標AとBの距離を求める
	float distance = Length(subtract);
	// 球と球の交差判定
	if (distance < colliderA->GetSize() + colliderB->GetSize()) {
		// コライダーAの衝突時コールバックを呼び出す
		controllerA->OnCollision(colliderB);
		// コライダーBの衝突時コールバックを呼び出す
		controllerB->OnCollision(colliderA);
	}
}

void CollisionManager::CheckAllCollisions() {
	// リスト内のペアを総当たり
	std::list<EntityController*>::iterator itrA = controllers_.begin();
	for (; itrA != controllers_.end(); ++itrA) {
		EntityController* colliderA = *itrA;
		// イテレータBイテレータAの次の要素から回す(重複判定を回避)
		std::list<EntityController*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != controllers_.end(); ++itrB) {
			EntityController* colliderB = *itrB;
			// ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}
