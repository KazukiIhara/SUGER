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

	// 同時発生個数のセット
	void SetCount(const uint32_t& count);

	// 繰り返し発生フラグセット
	void SetIsRepeat(const bool& isRepeat);

	// ランダムフラグセット
	void SetIsRandom(const bool& isRandom);

	// 発生場所のランダム閾値
	void SetRandomMinPosition(const Vector3& randomMinPosition);
	void SetRandomMaxPosition(const Vector3& randomMaxPosition);

	// 移動量のランダム閾値
	void SetRandomMinVelocity(const Vector3& randomMinVelocity);
	void SetRandomMaxVelocity(const Vector3& randomMaxVelocity);

	// 色のランダム閾値
	void SetRandomMinColor(const Vector3& randomMinColor);
	void SetRandomMaxColor(const Vector3& randomMaxColor);

	// 生存時間のランダム閾値
	void SetRandomMinLifeTime(float randomMinLifeTime);
	void SetRandomMaxLifeTime(float randomMaxLifeTime);

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