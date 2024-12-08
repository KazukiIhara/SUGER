// This
#include "SceneFactory.h"

#include "scene/gameScenes/sample/SampleScene.h"
#include "scene/gameScenes/load/LoadScene.h"
#include "scene/gameScenes/evaluation/EvaluationTaskScene.h"
#include "scene/gameScenes/CG3/CG3Scene.h"

BaseScene* SceneFactory::CreateScene(const std::string& sceneName) {
	// 次のシーンを生成
	BaseScene* newScene = nullptr;

	if (sceneName == "SAMPLE") {
		newScene = new SampleScene();
	} else if (sceneName == "LOAD") {
		newScene = new LoadScene();
	} else if (sceneName == "CG3") {
		newScene = new CG3Scene();
	} else if (sceneName == "EVALUATION") {
		newScene = new EvaluationScene();
	}

	return newScene;
}
