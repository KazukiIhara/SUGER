#include "Object2dController.h"

#include <cassert>

#include "2d/sprite/Sprite.h"

void Object2DController::Initialize(Sprite* object2d) {
	// nullptrだった場合assert
	assert(object2d);
	// オブジェクトをセット
	SetObject(object2d);
}

void Object2DController::SetObject(Sprite* object2d) {
	object2d_ = object2d;
}
