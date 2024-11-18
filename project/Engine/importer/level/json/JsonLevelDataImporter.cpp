#include "JsonLevelDataImporter.h"

#include "data/level/json/JsonLevelData.h"

#include "framework/SUGER.h"

void JsonLevelDataImporter::Import(JsonLevelData* jsonLevelData) {
	// 配置されているすべてのオブジェクトを生成
	for (ObjectData3D object : jsonLevelData->Get3DObjects()) {
		SUGER::CreateEntity(object.objectName, object.modelName, false, object.transform);
	}
}