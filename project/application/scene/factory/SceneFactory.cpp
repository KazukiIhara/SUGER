// This
#include "SceneFactory.h"

#include "scene/sample/SampleScene.h"
#include "scene/AL4/shootingCoaster/ShootingCoasterScene.h"
#include "scene/AL4/titleScene/TitleScene.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName) {
	// 次のシーンを生成
	BaseScene* newScene = nullptr;

	if (sceneName == "SAMPLE") {
		newScene = new SampleScene();
	} else if (sceneName == "SHOOTINGCOASTER") {
		newScene = new ShootingCoasterScene();
	} else if (sceneName=="TITLE") {
		newScene = new TitleScene();
	}

	return newScene;
}
