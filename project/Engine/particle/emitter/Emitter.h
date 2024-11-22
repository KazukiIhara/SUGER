#pragma once
#include "3d/empty/empty.h"
#include "particle/particle/Particle.h"

class Emitter:public Empty {
public:
	Emitter() = default;
	~Emitter() = default;

	// 初期化
	void Initialize()override;

	// 更新
	void Update()override;

	// パーティクル発生
	virtual void Emit();

	// パーティクルのセット
	void SetParticle(const std::string& particleName);

	// 発生数のセット
	void SetCount(const uint32_t& count);
	// 発生頻度のセット
	void SerFrequency(const float& frequency);
	// 繰り返し発生フラグのセット
	void SetIsRepeat(const bool& isRepeat);
	// ランダムフラグのセット
	void SetIsRandom(const bool& isRandom);

protected:
	// デルタタイム
	const float kDeltaTime_ = 1.0f / 60.0f;

	// セットするパーティクル
	Particle* particle_ = nullptr;

	// パーティクル発生設定
	EmitSetting emitSetting_{};
	// 発生数
	uint32_t count_ = 1;
	// 発生頻度
	float frequency_ = 0.5f;
	// 繰り返し発生させるかどうか
	bool isRepeat_ = false;
	// 頻度用時刻
	float frequencyTime_ = 0.0f;

	// ランダム値を使用するかどうか
	bool isRandom_ = false;

	// 発生場所のランダム閾値
	Vector3 randomMinTranslate_ = { -1.0f,-1.0f,-1.0f };
	Vector3 randomMaxTranslate_ = { 1.0f,1.0f,1.0f };

	// 移動量のランダム閾値
	Vector3	randomMinVelocity_ = { -1.0f,-1.0f,-1.0f };
	Vector3	randomMaxVelocity_ = { 1.0f,1.0f,1.0f };

	// 色のランダム閾値
	Vector3 randomMinColor_ = { 0.0f,0.0f,0.0f };
	Vector3	randomMaxColor_ = { 1.0f,1.0f,1.0f };

	// 生存時間のランダム閾値
	float randomMinLifeTime_ = 0.0f;
	float randomMaxLifeTime_ = 5.0f;

};
