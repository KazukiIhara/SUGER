#include "TextureManager.h"

#include "Logger.h"
#include "DirectXManager.h"
#include "DXGIManager.h"
#include "DirectXCommand.h"
#include "SRVManager.h"

void TextureManager::Initialize(DirectXManager* directXManager, SRVManager* srvManager) {
	SetDirectXCommon(directXManager);
	SetDXGIManager(directXManager_->GetDXGIManager());
	SetDxCommandManager(directXManager_->GetDirectXCommand());
	SetSrvManager(srvManager);
}

void TextureManager::Load(const std::string& filePath) {
	// テクスチャがすでに読み込まれているかチェック
	auto it = textures_.find(filePath);
	if (it != textures_.end()) {
		// すでに読み込まれている場合、早期リターン
		return;
	}

	// 今回ぶち込むテクスチャーの箱
	Texture& texture = textures_[filePath];
	DirectX::ScratchImage mipImage_ = LoadTexture(filePath);
	texture.metaData = mipImage_.GetMetadata();
	texture.resource = CreateTextureResource(texture.metaData);
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource = UploadTextureData(texture.resource.Get(), mipImage_);

	// コマンドのクローズと実行
	directXManager_->KickCommand();
	directXManager_->WaitGPU();
	directXManager_->ResetCommandList();

	// SRVを作成するDescriptorHeapの場所を決める
	texture.srvIndex = srvManager_->Allocate();
	// srvの作成
	srvManager_->CreateSrvTexture2d(texture.srvIndex, textures_[filePath].resource.Get(), texture.metaData.format, UINT(texture.metaData.mipLevels));

	// テクスチャ枚数上限チェック
	assert(srvManager_->IsLowerSrvMax());
}

const DirectX::TexMetadata& TextureManager::GetMetaData(const std::string& filePath) {
	assert(&GetTexture()[filePath]);
	Texture& texture = GetTexture()[filePath];
	return texture.metaData;
}

void TextureManager::SetDirectXCommon(DirectXManager* directX) {
	directXManager_ = directX;
}

void TextureManager::SetDXGIManager(DXGIManager* dxgi) {
	dxgiManager_ = dxgi;
}

void TextureManager::SetDxCommandManager(DirectXCommandManager* dxCommand) {
	dxCommand_ = dxCommand;
}

void TextureManager::SetSrvManager(SRVManager* srvManager) {
	srvManager_ = srvManager;
}

DirectX::ScratchImage TextureManager::LoadTexture(const std::string& filePath) {
	// テクスチャファイルを読んでプログラムで扱えるようにする
	DirectX::ScratchImage image{};
	std::wstring filePathW = Logger::ConvertString(filePath);
	HRESULT hr = DirectX::LoadFromWICFile(filePathW.c_str(), DirectX::WIC_FLAGS_FORCE_SRGB, nullptr, image);
	assert(SUCCEEDED(hr));

	// ミップマップの作成
	DirectX::ScratchImage mipImages{};
	hr = DirectX::GenerateMipMaps(image.GetImages(), image.GetImageCount(), image.GetMetadata(), DirectX::TEX_FILTER_SRGB, 0, mipImages);
	assert(SUCCEEDED(hr));

	//ミップマップ付きのデータを返す
	return mipImages;
}

Microsoft::WRL::ComPtr<ID3D12Resource> TextureManager::CreateTextureResource(const DirectX::TexMetadata& metadata) {
	// metadataを基にResourceの設定
	D3D12_RESOURCE_DESC resourceDesc{};
	resourceDesc.Width = UINT(metadata.width);	// Textureの幅
	resourceDesc.Height = UINT(metadata.height);// Textureの高さ
	resourceDesc.MipLevels = UINT16(metadata.mipLevels);// mipmapの数
	resourceDesc.DepthOrArraySize = UINT16(metadata.arraySize);// 奥行きor配列Textureの配列数
	resourceDesc.Format = metadata.format;// TextureのFormat
	resourceDesc.SampleDesc.Count = 1;// サンプリングカウント。1固定
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION(metadata.dimension);//textureの次元数。普段使っているのは2次元

	// 利用するHeapの設定。非常に便利な運用。02_04exで一般的なケース版がある
	D3D12_HEAP_PROPERTIES heapProperties{};
	heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;

	// Resourceの作成
	Microsoft::WRL::ComPtr<ID3D12Resource> resource = nullptr;
	HRESULT hr = dxgiManager_->GetDevice()->CreateCommittedResource(
		&heapProperties,// Heapの設定
		D3D12_HEAP_FLAG_NONE,// Heapの特殊な設定。特になし。
		&resourceDesc,// リソースの設定
		D3D12_RESOURCE_STATE_COPY_DEST,//データ転送される設定
		nullptr,// Clear最適値。使わないのでnullptr
		IID_PPV_ARGS(&resource));// 作成するResourceポインタへのポインタ
	assert(SUCCEEDED(hr));
	return resource;
}

[[nodiscard]]
Microsoft::WRL::ComPtr<ID3D12Resource> TextureManager::UploadTextureData(ID3D12Resource* texture, const DirectX::ScratchImage& mipImages) {
	std::vector<D3D12_SUBRESOURCE_DATA> subresources;
	DirectX::PrepareUpload(dxgiManager_->GetDevice(), mipImages.GetImages(), mipImages.GetImageCount(), mipImages.GetMetadata(), subresources);
	uint64_t intermediateSize = GetRequiredIntermediateSize(texture, 0, UINT(subresources.size()));
	Microsoft::WRL::ComPtr<ID3D12Resource> intermediateResource = directXManager_->CreateBufferResource(intermediateSize);
	UpdateSubresources(dxCommand_->GetList(), texture, intermediateResource.Get(), 0, 0, UINT(subresources.size()), subresources.data());
	// Textureへの転送後は利用できるよう、D3D12_RESOURCE_STATE_COPY_DESTからD3D12_RESOURCE_STATE_GENERIC_READへResourceStateを変更する
	D3D12_RESOURCE_BARRIER barrier{};
	barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
	barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
	barrier.Transition.pResource = texture;
	barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
	barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
	barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
	dxCommand_->GetList()->ResourceBarrier(1, &barrier);
	return intermediateResource;
}
