#pragma once

#include "particle/emitter/Emitter.h"

class EmitterController {
public:
	EmitterController() = default;
	~EmitterController() = default;

	// 初期化
	void Initialize(const std::string& name);

	// パーティクル発生
	void Emit();

	//
	// Setter
	//

	// スケールのセット
	void SetScale(const Vector3& scale);
	void SetScale(const float& scale);
	// 回転のセット
	void SetRotate(const Vector3& rotate);
	// トランスレートのセット
	void SetTranslate(const Vector3& translate);

	// 親トランスフォームのセット
	void SetParent(WorldTransform* parent);

	// パーティクルのセット
	void SetParticle(const std::string& particleName);

	// 繰り返し発生フラグセット
	void SetIsRepeat(const bool& isRepeat);


	//
	// Getter
	//

	// スケールの取得
	const Vector3& GetScale()const;
	// 回転の取得
	const Vector3& GetRotate()const;
	// 移動量の取得
	const Vector3& GetTranslate()const;

	// ワールド座標のゲッター
	Vector3 GetWorldPosition()const;

	// ワールドトランスフォームのポインタの取得
	WorldTransform* GetWorldTransformPtr();

private:
	// エミッター
	Emitter* emitter_ = nullptr;
};