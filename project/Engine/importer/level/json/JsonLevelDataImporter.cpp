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

void JsonLevelDataImporter::ImportRailControllPoint(JsonLevelData* jsonRailData, RailCamera* railCamera) {
	// 配置されている3Dオブジェクトから座標を取得して配置
	for (ObjectData3D object : jsonRailData->Get3DObjects()) {
		railCamera->PushBackControlPoint(object.transform.translate);
	}
}
