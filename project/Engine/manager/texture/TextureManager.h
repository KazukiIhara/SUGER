#pragma once

#include "structs/TextureStruct.h"

// 前方宣言
class DirectXManager;
class SRVUAVManager;

class TextureManager {
public: // 公開メンバ関数
	TextureManager() = default;
	~TextureManager() = default;

	// 初期化
	void Initialize(DirectXManager* directXManager, SRVUAVManager* srvManager);

	// テクスチャのロード
	void Load(const std::string& filePath);

	// Textureを渡す
	std::unordered_map<std::string, Texture>& GetTexture();

	// メタデータを渡す
	const DirectX::TexMetadata& GetMetaData(const std::string& filePath);


private: // 非公開メンバ関数
	// DirectXCommon
	void SetDirectXCommon(DirectXManager* directX);
	// SrvManager
	void SetSrvManager(SRVUAVManager* srvManager);

private:
	// Texture読み込み
	DirectX::ScratchImage LoadTexture(const std::string& filePath);
	// テクスチャリソースを作る
	Microsoft::WRL::ComPtr<ID3D12Resource> CreateTextureResource(const DirectX::TexMetadata& metadata);
	// テクスチャデータを送る
	Microsoft::WRL::ComPtr<ID3D12Resource> UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages);

private: // メンバ変数
	// テクスチャコンテナ
	std::unordered_map<std::string, Texture> textures_;
private: // インスタンス受け取り変数
	// DirectXCommon
	DirectXManager* directXManager_ = nullptr;
	// SrvManager
	SRVUAVManager* srvManager_ = nullptr;
};