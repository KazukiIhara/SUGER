#include "JsonLevelDataImporter.h"

#include "data/level/json/JsonLevelData.h"
#include "3d/cameras/railCamera/RailCamera.h"
#include "framework/SUGER.h"

void JsonLevelDataImporter::Import(JsonLevelData* jsonLevelData) {
	// 配置されているすべてのオブジェクトを生成
	for (ObjectData3D object : jsonLevelData->Get3DObjects()) {
		SUGER::Create3DObject(object.objectName, object.modelName, object.transform);
	}
}

void JsonLevelDataImporter::ImportLevelwithRailControllPoint(JsonLevelData* jsonRailData, RailCamera* railCamera) {
	// データ受け取り
	for (ObjectData3D object : jsonRailData->Get3DObjects()) {
		SUGER::Create3DObject(object.objectName, object.modelName, object.transform);
	}
	// データをシーンのカメラに挿入
	for (Vector3 controlPoint : jsonRailData->GetControlPoints()) {
		railCamera->PushBackControlPoint(controlPoint);
	}
}