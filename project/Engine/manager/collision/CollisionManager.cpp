#include "CollisionManager.h"

void CollisionManager::Initialize() {}

void CollisionManager::Update() {}

void CollisionManager::Finalize() {
	Reset();
}

void CollisionManager::Reset() {
	// リストの中身を初期化
	colliders_.clear();
}

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {
	// A,Bの座標を取得
	Vector3 positionA = colliderA->GetCenterPosition();
	Vector3 positionB = colliderB->GetCenterPosition();
	// 座標の差分ベクトル
	Vector3 subtract = positionB - positionA;
	// 座標AとBの距離を求める
	float distance = Length(subtract);
	// 球と球の交差判定
	if (distance < colliderA->GetRadius() + colliderB->GetRadius()) {
		// コライダーAの衝突時コールバックを呼び出す
		colliderA->OnCollision(colliderB);
		// コライダーBの衝突時コールバックを呼び出す
		colliderB->OnCollision(colliderA);
	}
}

void CollisionManager::CheckAllCollisions() {
	// リスト内のペアを総当たり
	std::list<Collider*>::iterator itrA = colliders_.begin();
	for (; itrA != colliders_.end(); ++itrA) {
		Collider* colliderA = *itrA;
		// イテレータBイテレータAの次の要素から回す(重複判定を回避)
		std::list<Collider*>::iterator itrB = itrA;
		itrB++;
		for (; itrB != colliders_.end(); ++itrB) {
			Collider* colliderB = *itrB;
			// ペアの当たり判定
			CheckCollisionPair(colliderA, colliderB);
		}
	}
}

void CollisionManager::AddCollider(BaseEntity* baseEntity) {
	colliders_.push_back(baseEntity);
}