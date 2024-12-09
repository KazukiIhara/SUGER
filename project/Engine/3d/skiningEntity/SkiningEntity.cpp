#include "SkiningEntity.h"

#include "framework/SUGER.h"

void SkiningEntity::Update() {
	// 基底クラスの更新
	Entity::Update();
	// スキニング処理
	model_->Skinning();
}
