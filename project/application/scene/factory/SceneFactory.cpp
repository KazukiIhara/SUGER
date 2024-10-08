// This
#include "SceneFactory.h"

#include "scene/sample/SampleScene.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName) {
	// 次のシーンを生成
	BaseScene* newScene = nullptr;

	// タイトルシーン
	if (sceneName == "SAMPLE") {
		newScene = new SampleScene();
	}

	return newScene;
}
