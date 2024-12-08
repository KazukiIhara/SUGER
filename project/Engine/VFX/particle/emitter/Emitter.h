#pragma once
#include "3d/empty/empty.h"
#include "enum/EmitterEnum.h"
#include "VFX/particle/particle/Particle.h"

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
	void SetFrequency(const float& frequency);
	// 繰り返し発生フラグのセット
	void SetIsRepeat(const bool& isRepeat);
	// 発生タイプのセット
	void SetEmitType(const EmitType& emitType);
	// ブレンドモードセット
	void SetBlendMode(const BlendMode& blendMode);

	// 
	// ランダム発生の閾値設定
	// 

	// サイズ最小値
	void SetMinSize(float minSize);
	// サイズ最大値
	void SetMaxSize(float maxSize);
	// 座標最小値
	void SetMinPosition(const Vector3& randomMinPosition);
	// 座標最大値
	void SetMaxPosition(const Vector3& randomMaxPosition);
	// 移動量最小値
	void SetMinVelocity(const Vector3& randomMinVelocity);
	// 移動量最大値
	void SetMaxVelocity(const Vector3& randomMaxVelocity);
	// 色最小値
	void SetMinColor(const Vector3& randomMinColor);
	// 色最大値
	void SetMaxColor(const Vector3& randomMaxColor);
	// 生存時間最小値
	void SetMinLifeTime(float randomMinLifeTime);
	// 生存時間最大値
	void SetMaxLifeTime(float randomMaxLifeTime);

protected:
	// 
	// 基本的な変数
	//

	// デルタタイム
	const float kDeltaTime_ = 1.0f / 60.0f;
	// セットするパーティクル
	Particle* particle_ = nullptr;
	// パーティクル発生設定
	EmitParamater emitParamater_{};
	// 発生の種類
	EmitType emitType_ = EmitType::kDefault;
	// ブレンドモード
	BlendMode blendMode_= BlendMode::kBlendModeAdd;
	// 発生数
	uint32_t count_ = 1;

	//
	// 繰り返し発生用の変数
	//

	// 発生頻度
	float frequency_ = 0.5f;
	// 繰り返し発生させるかどうか
	bool isRepeat_ = false;
	// 頻度用時刻
	float frequencyTime_ = 0.0f;

	//
	// ランダム発生用の変数
	//

	// 発生場所のランダム閾値
	Vector3 minTranslate_ = { 0.0f,0.0f,0.0f };
	Vector3 maxTranslate_ = { 0.0f,0.0f,0.0f };

	// サイズのランダム閾値
	float minSize_ = 1.0f;
	float maxSize_ = 1.0f;

	// 移動量のランダム閾値
	Vector3	minVelocity_ = { 0.0f,0.0f,0.0f };
	Vector3	maxVelocity_ = { 0.0f,0.0f,0.0f };

	// 色のランダム閾値
	Vector3 minColor_ = { 1.0f,1.0f,1.0f };
	Vector3	maxColor_ = { 1.0f,1.0f,1.0f };

	// 生存時間のランダム閾値
	float minLifeTime_ = 3.0f;
	float maxLifeTime_ = 3.0f;

	//
	// 放射発生用の変数
	//

	// 発生速度
	float speed_ = 1.0f;

};
