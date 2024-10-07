#pragma once

// C++
#include <cstdint>

// DirectX
#include <d3d12.h>

// DirectxTex
#include "externals/DirectXTex/DirectXTex.h"
#include "externals/DirectXTex/d3dx12.h"

#include "directX/includes/ComPtr.h"

// 前方宣言
class DirectXManager;
class SRVManager;

class TextureManager {
public: // 構造体
	// テクスチャ構造体
	struct Texture {
		// テクスチャリソース
		Microsoft::WRL::ComPtr<ID3D12Resource> resource;
		// メタデータ
		DirectX::TexMetadata metaData;
		// srvIndex
		uint32_t srvIndex;
	};

public: // 公開メンバ関数
	TextureManager() = default;
	~TextureManager() = default;

	// 初期化
	void Initialize(DirectXManager* directXManager, SRVManager* srvManager);

	// テクスチャのロード
	void Load(const std::string& filePath);

	// Textureを渡す
	std::unordered_map<std::string, Texture>& GetTexture() {
		return textures_;
	}
	// メタデータを渡す
	const DirectX::TexMetadata& GetMetaData(const std::string& filePath);


private: // 非公開メンバ関数

	// DirectXCommon
	void SetDirectXCommon(DirectXManager* directX);
	// SrvManager
	void SetSrvManager(SRVManager* srvManager);

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
	SRVManager* srvManager_ = nullptr;

};