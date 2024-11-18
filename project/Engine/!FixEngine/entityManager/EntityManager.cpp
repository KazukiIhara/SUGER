#include "EntityManager.h"

void EntityManager::Initialize() {}

void EntityManager::Update() {}

void EntityManager::Draw() {}

void EntityManager::Finalize() {}

std::string EntityManager::Create(const std::string& name, const std::string& filePath, const EulerTransform3D& transform) {
	return std::string();
}

Entity* EntityManager::Find(const std::string& name) {
	return nullptr;
}

void EntityManager::SetRequiredObjects(Camera* camera, PunctualLight* punctualLight) {}

void EntityManager::SetSceneCamera(Camera* camera) {}

void EntityManager::SetScenePunctualLight(PunctualLight* punctualLight) {}

void EntityManager::SetModelManager(ModelManager* modelManager) {}
