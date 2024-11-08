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

void CollisionManager::CheckCollisionPair(Collider* colliderA, Collider* colliderB) {}

void CollisionManager::CheckAllCollisions() {}

void CollisionManager::AddCollider(BaseEntity* baseEntity) {
	colliders_.push_back(baseEntity);
}