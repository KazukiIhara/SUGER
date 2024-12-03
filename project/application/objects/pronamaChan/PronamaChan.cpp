#include "PronamaChan.h"

void PronamaChan::OnCollision([[maybe_unused]] Collider* other) {
	// 衝突相手のカテゴリーを取得
	ColliderCategory category = other->GetColliderCategory();
	switch (category) {
	case kNone:
		SetColor(Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		break;
	}
}
