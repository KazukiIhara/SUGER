#include "JsonLevelDataImporter.h"

#include "data/level/json/JsonLevelData.h"
#include "3d/cameras/railCamera/RailCamera.h"
#include "objects/baroon/Baroon.h"

#include "framework/SUGER.h"

void JsonLevelDataImporter::Import(JsonLevelData* jsonLevelData) {
	// 配置されているすべてのオブジェクトを生成
	for (ObjectData3D object : jsonLevelData->Get3DObjects()) {
		SUGER::Create3DObject(object.objectName, object.modelName, object.transform);
	}
}

void JsonLevelDataImporter::ImportLevel(JsonLevelData* jsonRailData, RailCamera* railCamera, std::list<std::unique_ptr<Baroon>> &baroons) {
	// データ受け取り
	for (ObjectData3D object : jsonRailData->Get3DObjects()) {
		SUGER::Create3DObject(object.objectName, object.modelName, object.transform);
	}
	// データをシーンのカメラに挿入
	for (Vector3 controlPoint : jsonRailData->GetControlPoints()) {
		railCamera->PushBackControlPoint(controlPoint);
	}
	for (ObjectData3D baroon : jsonRailData->GetBaroons()) {
		// バルーンの生成と初期化
		std::unique_ptr<Baroon> newBaroon = std::make_unique<Baroon>();
		newBaroon->Initialize(baroon.objectName, baroon.modelName, baroon.transform);
		// コライダーカテゴリーを設定
		newBaroon->SetCategory(kBaroon);
		baroons.push_back(std::move(newBaroon));
	}
}