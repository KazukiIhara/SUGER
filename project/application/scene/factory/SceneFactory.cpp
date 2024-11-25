// This
#include "SceneFactory.h"

#include "scene/gameScenes/sample/SampleScene.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName) {
	// 次のシーンを生成
	BaseScene* newScene = nullptr;

	if (sceneName == "SAMPLE") {
		newScene = new SampleScene();
	}

	return newScene;
}
