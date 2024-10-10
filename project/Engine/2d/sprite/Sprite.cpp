// This
#include "Sprite.h"

// MyHedder
#include "framework/SUGER.h"
#include "manager/window/WindowManager.h"
#include "externals/DirectXTex/DirectXTex.h"

void Sprite::Initialize(const std::string& textureFilePath) {

	// ワールドトランスフォームを初期化
	worldTransform_.Initialize();
	// マテリアルを初期化
	material_.color = { 1.0f,1.0f,1.0f,1.0f };
	material_.uvTransformMatrix = MakeIdentityMatrix4x4();
	// テクスチャ左上座標
	textureLeftTop = { 0.0f,0.0f };
	// テクスチャ切り出しサイズ
	textureSize = { 512.0f,512.0f };

	SetTextureHandle(textureFilePath);
	SUGER::LoadTexture(textureFilePath);

#pragma region 頂点データ
	/*頂点リソースの作成*/
	CreateVertexResource();
	/*頂点バッファビューの作成*/
	CreateVretexBufferView();
	/*頂点データの書き込み*/
	MapVertexData();
#pragma endregion

#pragma region インデックスデータ
	/*描画用のインデックスリソースを作成*/
	CreateIndexResource();
	/*インデックスバッファビューの作成*/
	CreateIndexBufferView();
	/*インデックスリソースにデータを書き込む*/
	MapIndexResource();
#pragma endregion

#pragma region マテリアルデータ
	/*マテリアル用のリソース作成*/
	CreateMaterialResource();
	/*マテリアルにデータを書き込む*/
	MapMaterialData();
#pragma endregion

#pragma region 変換データ
	/*wvp用のリソース作成*/
	CreateWVPResource();
	/*データを書き込む*/
	MapWVPData();
#pragma endregion

	AdjustTextureSize();
}

void Sprite::Update() {
	// アンカーポイントの設定
	float left = 0.0f - anchorPoint.x;
	float right = 01.0f - anchorPoint.x;
	float top = 0.0f - anchorPoint.y;
	float bottom = 1.0f - anchorPoint.y;

	// 左右反転
	if (isFlipX_) {
		left = -left;
		right = -right;
	}
	// 上下反転
	if (isFlipY_) {
		top = -top;
		bottom = -bottom;
	}

	// データを書き込む
	vertexData_[0].position = { left,bottom,0.0f,1.0f };//左下
	vertexData_[1].position = { left,top,0.0f,1.0f };//左上
	vertexData_[2].position = { right,bottom,0.0f,1.0f };//右下
	vertexData_[3].position = { right,top,0.0f,1.0f };//右上


	// メタデータを取得
	const DirectX::TexMetadata& metaData =
		SUGER::GetTextureMetaData(textureFilePath_);
	float texLeft = textureLeftTop.x / metaData.width;
	float texRight = (textureLeftTop.x + textureSize.x) / metaData.width;
	float texTop = textureLeftTop.y / metaData.height;
	float texBottom = (textureLeftTop.y + textureSize.y) / metaData.height;

	// データを書き込む
	vertexData_[0].texcoord = { texLeft,texBottom };
	vertexData_[1].texcoord = { texLeft,texTop };
	vertexData_[2].texcoord = { texRight,texBottom };
	vertexData_[3].texcoord = { texRight,texTop };


	// 座標を反映
	worldTransform_.translate = { transform.position.x,transform.position.y,0.0f };
	// 回転を反映
	worldTransform_.rotate = { 0.0f,0.0f,transform.rotate };
	// サイズを反映
	worldTransform_.scale = { transform.size.x,transform.size.y,1.0f };

	// ワールド行列の更新
	worldTransform_.Update();
	Matrix4x4 projectionMatrix = MakeOrthographicMatrix(0.0f, 0.0f, float(WindowManager::kClientWidth), float(WindowManager::kClientHeight), 0.0f, 100.0f);
	*wvpData_ = worldTransform_.worldMatrix_ * projectionMatrix;

	// マテリアルデータの更新
	material_.uvTransformMatrix = MakeUVMatrix(uvTransform.scale, uvTransform.rotateZ, uvTransform.translate);
	materialData_->uvTransformMatrix = material_.uvTransformMatrix;

}

void Sprite::Draw(BlendMode blendMode) {
	//PSOを設定
	SUGER::GetDirectXCommandList()->SetPipelineState(SUGER::GetPipelineState(kObject2d, blendMode));
	/*VBVの設定*/
	SUGER::GetDirectXCommandList()->IASetVertexBuffers(0, 1, &vertexBufferView_);
	/*IBVの設定*/
	SUGER::GetDirectXCommandList()->IASetIndexBuffer(&indexBufferView_);
	/*マテリアルCBufferの場所を設定*/
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	/*wvp用のCBufferの場所を設定*/
	SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(1, transformationResource_->GetGPUVirtualAddress());
	/*SRVのDescriptorTableの先頭を設定*/
	SUGER::SetGraphicsRootDescriptorTable(2, SUGER::GetTexture()[textureFilePath_].srvIndex);
	//描画！(DrawCall/ドローコール)
	SUGER::GetDirectXCommandList()->DrawIndexedInstanced(6, 1, 0, 0, 0);
}

void Sprite::CreateVertexResource() {
	vertexResource_ = SUGER::CreateBufferResource(sizeof(sVertexData2D) * 6);
}

void Sprite::CreateVretexBufferView() {
	//頂点バッファビューを作成する
	//リソースの先頭アドレスから使う
	vertexBufferView_.BufferLocation = vertexResource_->GetGPUVirtualAddress();
	//使用するリソースのサイズは頂点4つ分のサイズ
	vertexBufferView_.SizeInBytes = sizeof(sVertexData2D) * 4;
	//1頂点あたりのサイズ
	vertexBufferView_.StrideInBytes = sizeof(sVertexData2D);
}

void Sprite::MapVertexData() {
	//頂点リソースにデータを書き込む
	vertexData_ = nullptr;

	//書き込むためのアドレスを取得
	vertexResource_->Map(0, nullptr, reinterpret_cast<void**>(&vertexData_));

	//1枚目の三角形
	vertexData_[0].position = { 0.0f,1.0f,0.0f,1.0f };//左下
	vertexData_[0].texcoord = { 0.0f,1.0f };
	vertexData_[1].position = { 0.0f,0.0f,0.0f,1.0f };//左上
	vertexData_[1].texcoord = { 0.0f,0.0f };
	vertexData_[2].position = { 1.0f,1.0f,0.0f,1.0f };//右下
	vertexData_[2].texcoord = { 1.0f,1.0f };
	vertexData_[3].position = { 1.0f,0.0f,0.0f,1.0f };//右上
	vertexData_[3].texcoord = { 1.0f,0.0f };
}

void Sprite::CreateIndexResource() {
	indexResource_ = SUGER::CreateBufferResource(sizeof(uint32_t) * 6);
}

void Sprite::CreateIndexBufferView() {
	/*リソースの先頭アドレスから使う*/
	indexBufferView_.BufferLocation = indexResource_->GetGPUVirtualAddress();
	/*使用するリソースのサイズはインデックス6つ分*/
	indexBufferView_.SizeInBytes = sizeof(uint32_t) * 6;
	/*インデックスはuint32_tとする*/
	indexBufferView_.Format = DXGI_FORMAT_R32_UINT;
}

void Sprite::MapIndexResource() {
	/*インデックスリソースにデータを書き込む*/
	indexData_ = nullptr;
	indexResource_->Map(0, nullptr, reinterpret_cast<void**>(&indexData_));
	indexData_[0] = 0;	indexData_[1] = 1;	indexData_[2] = 2;
	indexData_[3] = 1;	indexData_[4] = 3;	indexData_[5] = 2;
}

void Sprite::CreateMaterialResource() {
	/*マテリアル用のリソースを作る*/
	materialResource_ = SUGER::CreateBufferResource(sizeof(sMaterial2D));
}

void Sprite::MapMaterialData() {
	materialData_ = nullptr;
	/*書き込むためのアドレスを取得*/
	materialResource_->Map(0, nullptr, reinterpret_cast<void**>(&materialData_));
	/*マテリアルデータを書き込む*/
	materialData_->color = material_.color;
	materialData_->uvTransformMatrix = material_.uvTransformMatrix;
}

void Sprite::CreateWVPResource() {
	/*WVP用のリソースを作る*/
	transformationResource_ = SUGER::CreateBufferResource(sizeof(Matrix4x4));
}

void Sprite::MapWVPData() {
	/*データを書き込む*/
	wvpData_ = nullptr;
	/*データを書き込むためのアドレスを取得*/
	transformationResource_->Map(0, nullptr, reinterpret_cast<void**>(&wvpData_));
	/*単位行列を書き込んでおく*/
	*wvpData_ = MakeIdentityMatrix4x4();
}

void Sprite::AdjustTextureSize() {
	// テクスチャデータ取得
	const DirectX::TexMetadata& metaData = SUGER::GetTextureMetaData(textureFilePath_);

	textureSize.x = static_cast<float>(metaData.width);
	textureSize.y = static_cast<float>(metaData.height);
	// 画面サイズをテクスチャサイズに合わせる
	transform.size = textureSize;
}
