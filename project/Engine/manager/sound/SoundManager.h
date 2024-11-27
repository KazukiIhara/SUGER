#pragma once

// C++
#include <fstream>
#include <wrl.h>
#include <map>

// MyHedder
#include "structs/SoundStruct.h"

class SoundManager {
public:
	SoundManager() = default;
	~SoundManager() = default;

	// 初期化
	void Initialize();
	// 終了
	void Finalize();
	// コンテナをクリア
	void ClearContainer();
	// 読み込み
	void LoadWave(const std::string& filename, const std::string& directoryPath);

	// 通常再生
	void PlayWave(const std::string& filename);
	// 音声停止
	void StopWave(const std::string& filename);
	// ループ再生
	void PlayWaveLoop(const std::string& filename, uint32_t loopCount = XAUDIO2_LOOP_INFINITE);
	// ループ再生停止
	void StopWaveLoop(const std::string& filename);

	// 統一された停止処理
	void StopAll(const std::string& filename);
	// 検索
	SoundData* FindWave(const std::string& filename);

private:
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;

	// サウンドデータコンテナ
	std::map<std::string, std::unique_ptr<SoundData>> sounds_;
};
