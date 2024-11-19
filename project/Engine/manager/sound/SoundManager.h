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
	// 再生
	void PlayWave(const std::string& filename);
	// 検索
	SoundData* FindWave(const std::string& filename);

private:
	Microsoft::WRL::ComPtr<IXAudio2> xAudio2;
	IXAudio2MasteringVoice* masterVoice;

	// サウンドデータコンテナ
	std::map<std::string, std::unique_ptr<SoundData>> sounds_;
};
