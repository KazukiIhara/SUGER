// This
#include "Model.h"

// C++ 
#include <cassert>
#include <filesystem>

// MyHedder
#include "framework/SUGER.h"

void Model::Initialize(const std::string& filename) {
	// モデルデータ読み込み
	LoadModel(filename);

	// マテリアル初期化
	for (auto& mesh : modelData_.meshes) {
		Material3D material;
		material.color = mesh.material.color;
		material.enbleLighting = true;
		material.shininess = 40.0f;
		material.uvTransformMatrix = MakeIdentityMatrix4x4();
		materials_.push_back(material);
		UVTransform identity = { {1.0f,1.0},0.0f,{0.0f,0.0f} };
		uvTransforms_.push_back(identity);
	}

#pragma region 頂点データ
	/*頂点リソースの作成*/
	CreateVertexResource();
	/*頂点バッファビューの作成*/
	CreateVertexBufferView();
	/*頂点データの書き込み*/
	MapVertexData();
#pragma endregion

#pragma region インデックスデータ
	/*描画用のインデックスリソースを作成*/
	CreateIndexResource();
	/*インデックスバッファビューの作成*/
	CreateIndexBufferView();
	/*インデックスリソースにデータを書き込む*/
	MapIndexData();
#pragma endregion

#pragma region マテリアルデータ
	/*マテリアル用のリソース作成*/
	CreateMaterialResource();
	/*マテリアルにデータを書き込む*/
	MapMaterialData();
#pragma endregion
}


void Model::Update() {

#pragma region Animation
	animationTime += 1.0f / 60.0f;
	animationTime = std::fmod(animationTime, animation_.duration);

	ApplyAnimation(skeleton_, animation_, animationTime);
	SkeletonUpdate(skeleton_);
	SkinClusterUpdate(skinCluster_, skeleton_);
#pragma endregion

	// マテリアルの更新
	for (size_t i = 0; i < materials_.size(); ++i) {
		materialData_[i]->color = materials_[i].color;
		materialData_[i]->enbleLighting = materials_[i].enbleLighting;
		materialData_[i]->shininess = materials_[i].shininess;
		materials_[i].uvTransformMatrix = MakeUVMatrix(uvTransforms_[i].scale, uvTransforms_[i].rotateZ, uvTransforms_[i].translate);
		materialData_[i]->uvTransformMatrix = materials_[i].uvTransformMatrix;
	}
}

void Model::Draw() {

	for (size_t i = 0; i < modelData_.meshes.size(); ++i) {

		D3D12_VERTEX_BUFFER_VIEW vbvs[2] = {
			vertexBufferViews_[i],
			skinCluster_.influenceBufferView,
		};

		// VBVを設定
		SUGER::GetDirectXCommandList()->IASetVertexBuffers(0, 2, vbvs);
		// IBVを設定
		SUGER::GetDirectXCommandList()->IASetIndexBuffer(&indexBufferViews_[i]);
		// マテリアルCBufferの場所を設定
		SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(0, materialResources_[i]->GetGPUVirtualAddress());
		if (modelData_.meshes[i].material.haveUV_) {
			// SRVセット
			SUGER::SetGraphicsRootDescriptorTable(4, SUGER::GetTexture()[modelData_.meshes[i].material.textureFilePath].srvIndex);
			// Skinning用SRVセット
			SUGER::SetGraphicsRootDescriptorTable(5, skinClusterSrvIndex_);
			// 描画！(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
			SUGER::GetDirectXCommandList()->DrawIndexedInstanced(UINT(modelData_.meshes[i].indices.size()), 1, 0, 0, 0);
		} else {
			// TODO:UVなしの時の処理
		}
	}
}

void Model::DrawPlaneParticle(const uint32_t& instanceCount, const std::string& textureFileName) {
	for (size_t i = 0; i < modelData_.meshes.size(); ++i) {
		// VBVを設定
		SUGER::GetDirectXCommandList()->IASetVertexBuffers(0, 1, &vertexBufferViews_[i]);
		// IBVを設定
		SUGER::GetDirectXCommandList()->IASetIndexBuffer(&indexBufferViews_[i]);
		// マテリアルCBufferの場所を設定
		SUGER::GetDirectXCommandList()->SetGraphicsRootConstantBufferView(0, materialResources_[i]->GetGPUVirtualAddress());
		// SRVセット
		SUGER::SetGraphicsRootDescriptorTable(2, SUGER::GetTexture()[textureFileName].srvIndex);
		// 描画！(DrawCall/ドローコール)。3頂点で1つのインスタンス。インスタンスについては今後
		SUGER::GetDirectXCommandList()->DrawIndexedInstanced(UINT(modelData_.meshes[i].indices.size()), instanceCount, 0, 0, 0);
	}
}

void Model::LoadModel(const std::string& filename, const std::string& directoryPath) {
	// 対応する拡張子のリスト
	std::vector<std::string> supportedExtensions = { ".obj", ".gltf" };

	// ディレクトリ内のファイルを検索
	// モデルファイルが入っているディレクトリ
	std::string fileDirectoryPath = directoryPath + "/" + filename;
	// filesystem用
	std::filesystem::path modelDirectoryPath(fileDirectoryPath);

	std::string modelFilePath;

	for (const auto& entry : std::filesystem::directory_iterator(modelDirectoryPath)) {
		if (entry.is_regular_file()) {
			std::string ext = entry.path().extension().string();
			// 対応する拡張子かチェック
			if (std::find(supportedExtensions.begin(), supportedExtensions.end(), ext) != supportedExtensions.end()) {
				if (entry.path().stem().string() == filename) {
					modelFilePath = entry.path().string();
					break;
				}
			}
		}
	}

	// ファイルが見つからなかった場合はエラー
	if (modelFilePath.empty()) {
		std::cerr << "Error: Model file not found or unsupported format." << std::endl;
		return;
	}

	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(modelFilePath.c_str(), aiProcess_FlipWindingOrder | aiProcess_FlipUVs | aiProcess_Triangulate);
	assert(scene && scene->HasMeshes());

	// ノード読み込み
	modelData_.rootNode = ReadNode(scene->mRootNode);

	std::vector<MaterialData> materials(scene->mNumMaterials);

	for (uint32_t materialIndex = 0; materialIndex < scene->mNumMaterials; ++materialIndex) {
		aiMaterial* material = scene->mMaterials[materialIndex];
		MaterialData materialData;
		if (material->GetTextureCount(aiTextureType_DIFFUSE) != 0) {
			aiString textureFilePath;
			material->GetTexture(aiTextureType_DIFFUSE, 0, &textureFilePath);
			materialData.textureFilePath = fileDirectoryPath + "/" + textureFilePath.C_Str();
			SUGER::LoadTexture(materialData.textureFilePath);
			materialData.haveUV_ = true;
		} else {
			materialData.haveUV_ = false;
		}
		materialData.color = { 1.0f, 1.0f, 1.0f, 1.0f };
		materials[materialIndex] = materialData;
	}

	for (uint32_t meshIndex = 0; meshIndex < scene->mNumMeshes; ++meshIndex) {
		aiMesh* mesh = scene->mMeshes[meshIndex];
		assert(mesh->HasNormals());

		MeshData meshData;
		meshData.material = materials[mesh->mMaterialIndex];


		if (mesh->HasTextureCoords(0)) { // UVあり

			// 最初に頂点数分のメモリを確保
			meshData.vertices.resize(mesh->mNumVertices);

			// 頂点解析
			for (uint32_t vertexIndex = 0; vertexIndex < mesh->mNumVertices; ++vertexIndex) {
				aiVector3D& position = mesh->mVertices[vertexIndex];
				aiVector3D& normal = mesh->mNormals[vertexIndex];
				aiVector3D& texcoord = mesh->mTextureCoords[0][vertexIndex];

				meshData.vertices[vertexIndex].position = { -position.x,position.y,position.z,1.0f };
				meshData.vertices[vertexIndex].normal = { -normal.x,normal.y,normal.z };
				meshData.vertices[vertexIndex].texcoord = { texcoord.x,texcoord.y };
			}
			// index解析
			for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
				aiFace& face = mesh->mFaces[faceIndex];
				assert(face.mNumIndices == 3);

				for (uint32_t element = 0; element < face.mNumIndices; ++element) {
					uint32_t vertexIndex = face.mIndices[element];
					meshData.indices.push_back(vertexIndex);
				}
			}

			for (uint32_t boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex) {
				aiBone* bone = mesh->mBones[boneIndex];
				std::string jointName = bone->mName.C_Str();
				JointWeightData& jointWeightData = modelData_.skinClusterData[jointName];

				aiMatrix4x4 bindPoseMatrixAssimp = bone->mOffsetMatrix.Inverse();
				aiVector3D scale, translate;
				aiQuaternion rotate;
				bindPoseMatrixAssimp.Decompose(scale, rotate, translate);
				Matrix4x4 bindPoseMatrix = MakeAffineMatrix(
					{ scale.x,scale.y,scale.z },
					{ rotate.x,-rotate.y,-rotate.z,rotate.w },
					{ -translate.x,translate.y,translate.z }
				);
				jointWeightData.inverseBindPoseMatrix = Inverse(bindPoseMatrix);

				for (uint32_t weightIndex = 0; weightIndex < bone->mNumWeights; weightIndex++) {
					jointWeightData.vertexWeights.push_back({ bone->mWeights[weightIndex].mWeight,bone->mWeights[weightIndex].mVertexId });
				}

			}

		} else { // UVなし
			for (uint32_t faceIndex = 0; faceIndex < mesh->mNumFaces; ++faceIndex) {
				aiFace& face = mesh->mFaces[faceIndex];
				assert(face.mNumIndices == 3);

				for (uint32_t element = 0; element < face.mNumIndices; ++element) {
					uint32_t vertexIndex = face.mIndices[element];
					aiVector3D& position = mesh->mVertices[vertexIndex];
					aiVector3D& normal = mesh->mNormals[vertexIndex];
					VertexData3DUnUV vertex;
					vertex.position = { position.x, position.y, position.z, 1.0f };
					vertex.normal = { normal.x, normal.y, normal.z };
					vertex.position.x *= -1.0f;
					vertex.normal.x *= -1.0f;
					meshData.verticesUnUV.push_back(vertex);
				}
			}
		}

		modelData_.meshes.push_back(meshData);
	}
	// アニメーション読み込み
	animation_ = LoadAnimationFile(filename);
	// スケルトン作成
	skeleton_ = CreateSkeleton(modelData_.rootNode);
	// スキンクラスター作成
	skinCluster_ = CreateSkinCluster(skeleton_, modelData_);
}

// 球体の頂点データを生成する関数
void Model::GenerateSphere(const std::string& textureFilePath) {

	// テクスチャをロード
	SUGER::LoadTexture(textureFilePath);

	const float kLonEvery = std::numbers::pi_v<float> *2.0f / float(kSubdivision);
	const float kLatEvery = std::numbers::pi_v<float> / float(kSubdivision);

	MeshData meshData;
	meshData.material.textureFilePath = textureFilePath;
	meshData.material.haveUV_ = true;
	meshData.vertices.resize(kSubdivision * kSubdivision * 6);
	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -std::numbers::pi_v<float> / 2.0f + kLatEvery * latIndex;
		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			uint32_t start = (latIndex * kSubdivision + lonIndex) * 6;
			float lon = lonIndex * kLonEvery;

			// a
			meshData.vertices[start].position.x = std::cosf(lat) * std::cosf(lon);
			meshData.vertices[start].position.y = std::sinf(lat);
			meshData.vertices[start].position.z = std::cosf(lat) * std::sinf(lon);
			meshData.vertices[start].position.w = 1.0f;
			meshData.vertices[start].texcoord = { float(lonIndex) / float(kSubdivision), 1.0f - float(latIndex) / float(kSubdivision) };

			meshData.vertices[start].normal.x = meshData.vertices[start].position.x;
			meshData.vertices[start].normal.y = meshData.vertices[start].position.y;
			meshData.vertices[start].normal.z = meshData.vertices[start].position.z;

			// b
			meshData.vertices[start + 1].position.x = std::cosf(lat + kLatEvery) * std::cosf(lon);
			meshData.vertices[start + 1].position.y = std::sinf(lat + kLatEvery);
			meshData.vertices[start + 1].position.z = std::cosf(lat + kLatEvery) * std::sinf(lon);
			meshData.vertices[start + 1].position.w = 1.0f;
			meshData.vertices[start + 1].texcoord = { float(lonIndex) / float(kSubdivision), 1.0f - float(latIndex + 1.0f) / float(kSubdivision) };

			meshData.vertices[start + 1].normal.x = meshData.vertices[start + 1].position.x;
			meshData.vertices[start + 1].normal.y = meshData.vertices[start + 1].position.y;
			meshData.vertices[start + 1].normal.z = meshData.vertices[start + 1].position.z;

			// c
			meshData.vertices[start + 2].position.x = std::cosf(lat) * std::cosf(lon + kLonEvery);
			meshData.vertices[start + 2].position.y = std::sinf(lat);
			meshData.vertices[start + 2].position.z = std::cosf(lat) * std::sinf(lon + kLonEvery);
			meshData.vertices[start + 2].position.w = 1.0f;
			meshData.vertices[start + 2].texcoord = { float(lonIndex + 1.0f) / float(kSubdivision), 1.0f - float(latIndex) / float(kSubdivision) };

			meshData.vertices[start + 2].normal.x = meshData.vertices[start + 2].position.x;
			meshData.vertices[start + 2].normal.y = meshData.vertices[start + 2].position.y;
			meshData.vertices[start + 2].normal.z = meshData.vertices[start + 2].position.z;

			// b
			meshData.vertices[start + 3].position.x = std::cosf(lat + kLatEvery) * std::cosf(lon);
			meshData.vertices[start + 3].position.y = std::sinf(lat + kLatEvery);
			meshData.vertices[start + 3].position.z = std::cosf(lat + kLatEvery) * std::sinf(lon);
			meshData.vertices[start + 3].position.w = 1.0f;
			meshData.vertices[start + 3].texcoord = { float(lonIndex) / float(kSubdivision), 1.0f - float(latIndex + 1.0f) / float(kSubdivision) };

			meshData.vertices[start + 3].normal.x = meshData.vertices[start + 3].position.x;
			meshData.vertices[start + 3].normal.y = meshData.vertices[start + 3].position.y;
			meshData.vertices[start + 3].normal.z = meshData.vertices[start + 3].position.z;

			// d
			meshData.vertices[start + 4].position.x = std::cosf(lat + kLatEvery) * std::cosf(lon + kLonEvery);
			meshData.vertices[start + 4].position.y = std::sinf(lat + kLatEvery);
			meshData.vertices[start + 4].position.z = std::cosf(lat + kLatEvery) * std::sinf(lon + kLonEvery);
			meshData.vertices[start + 4].position.w = 1.0f;
			meshData.vertices[start + 4].texcoord = { float(lonIndex + 1.0f) / float(kSubdivision), 1.0f - float(latIndex + 1.0f) / float(kSubdivision) };

			meshData.vertices[start + 4].normal.x = meshData.vertices[start + 4].position.x;
			meshData.vertices[start + 4].normal.y = meshData.vertices[start + 4].position.y;
			meshData.vertices[start + 4].normal.z = meshData.vertices[start + 4].position.z;

			// c
			meshData.vertices[start + 5].position.x = std::cosf(lat) * std::cosf(lon + kLonEvery);
			meshData.vertices[start + 5].position.y = std::sinf(lat);
			meshData.vertices[start + 5].position.z = std::cosf(lat) * std::sinf(lon + kLonEvery);
			meshData.vertices[start + 5].position.w = 1.0f;
			meshData.vertices[start + 5].texcoord = { float(lonIndex + 1.0f) / float(kSubdivision), 1.0f - float(latIndex) / float(kSubdivision) };

			meshData.vertices[start + 5].normal.x = meshData.vertices[start + 5].position.x;
			meshData.vertices[start + 5].normal.y = meshData.vertices[start + 5].position.y;
			meshData.vertices[start + 5].normal.z = meshData.vertices[start + 5].position.z;
		}
	}

	modelData_.meshes.push_back(meshData);
}


void Model::CreateSphere(const std::string& textureFilePath) {

	// スフィアの頂点作成
	GenerateSphere(textureFilePath);

	// マテリアル初期化
	Material3D material;
	material.color = { 1.0f,1.0f,1.0f,1.0f };
	material.enbleLighting = true;
	material.shininess = 40.0f;
	material.uvTransformMatrix = MakeIdentityMatrix4x4();
	materials_.push_back(material);

	UVTransform identity = { {1.0f,1.0f},0.0f,{0.0f,0.0f} };
	uvTransforms_.push_back(identity);

#pragma region 頂点データ
	/*頂点リソースの作成*/
	CreateVertexResource();
	/*頂点バッファビューの作成*/
	CreateVertexBufferView();
	/*頂点データの書き込み*/
	MapVertexData();
#pragma endregion

#pragma region マテリアルデータ
	/*マテリアル用のリソース作成*/
	CreateMaterialResource();
	/*マテリアルにデータを書き込む*/
	MapMaterialData();
#pragma endregion
}

void Model::GeneratePlane(const std::string& textureFilePath) {
	// テクスチャをロード
	SUGER::LoadTexture(textureFilePath);

	MeshData meshData;
	meshData.material.textureFilePath = textureFilePath;
	meshData.material.haveUV_ = true;

	// 頂点データの設定
	meshData.vertices.push_back({ .position = { 1.0f,  1.0f, 0.0f, 1.0f }, .texcoord = { 0.0f, 0.0f }, .normal = { 0.0f, 0.0f, 1.0f } });
	meshData.vertices.push_back({ .position = { -1.0f,  1.0f, 0.0f, 1.0f }, .texcoord = { 1.0f, 0.0f }, .normal = { 0.0f, 0.0f, 1.0f } });
	meshData.vertices.push_back({ .position = { 1.0f, -1.0f, 0.0f, 1.0f }, .texcoord = { 0.0f, 1.0f }, .normal = { 0.0f, 0.0f, 1.0f } });
	meshData.vertices.push_back({ .position = { -1.0f, -1.0f, 0.0f, 1.0f }, .texcoord = { 1.0f, 1.0f }, .normal = { 0.0f, 0.0f, 1.0f } });

	// インデックスデータの設定
	meshData.indices.push_back(0);
	meshData.indices.push_back(1);
	meshData.indices.push_back(2);
	meshData.indices.push_back(2);
	meshData.indices.push_back(1);
	meshData.indices.push_back(3);

	meshData.material.color = { 1.0f, 1.0f, 1.0f, 1.0f };

	// モデルにメッシュを追加
	modelData_.meshes.push_back(meshData);
}

void Model::CreatePlane(const std::string& textureFilePath) {

	// 板ポリの頂点作成
	GeneratePlane(textureFilePath);

	// マテリアル初期化
	Material3D material;
	material.color = { 1.0f,1.0f,1.0f,1.0f };
	material.enbleLighting = true;
	material.shininess = 40.0f;
	material.uvTransformMatrix = MakeIdentityMatrix4x4();
	materials_.push_back(material);

	UVTransform identity = { {1.0f,1.0f},0.0f,{0.0f,0.0f} };
	uvTransforms_.push_back(identity);

#pragma region 頂点データ
	/*頂点リソースの作成*/
	CreateVertexResource();
	/*頂点バッファビューの作成*/
	CreateVertexBufferView();
	/*頂点データの書き込み*/
	MapVertexData();
#pragma endregion

#pragma region インデックスデータ
	/*描画用のインデックスリソースを作成*/
	CreateIndexResource();
	/*インデックスバッファビューの作成*/
	CreateIndexBufferView();
	/*インデックスリソースにデータを書き込む*/
	MapIndexData();
#pragma endregion

#pragma region マテリアルデータ
	/*マテリアル用のリソース作成*/
	CreateMaterialResource();
	/*マテリアルにデータを書き込む*/
	MapMaterialData();
#pragma endregion

}

void Model::CreateVertexResource() {
	for (auto& mesh : modelData_.meshes) {
		Microsoft::WRL::ComPtr<ID3D12Resource> vertexResource;
		if (mesh.material.haveUV_) {
			vertexResource = SUGER::CreateBufferResource(sizeof(VertexData3D) * mesh.vertices.size());
		} else {
			vertexResource = SUGER::CreateBufferResource(sizeof(VertexData3DUnUV) * mesh.verticesUnUV.size());
		}
		vertexResources_.push_back(vertexResource);
	}
}

void Model::CreateVertexBufferView() {
	for (size_t i = 0; i < modelData_.meshes.size(); ++i) {
		D3D12_VERTEX_BUFFER_VIEW vertexBufferView;
		vertexBufferView.BufferLocation = vertexResources_[i]->GetGPUVirtualAddress();
		if (modelData_.meshes[i].material.haveUV_) {
			vertexBufferView.SizeInBytes = UINT(sizeof(VertexData3D) * modelData_.meshes[i].vertices.size());
			vertexBufferView.StrideInBytes = sizeof(VertexData3D);
		} else {
			vertexBufferView.SizeInBytes = UINT(sizeof(VertexData3DUnUV) * modelData_.meshes[i].verticesUnUV.size());
			vertexBufferView.StrideInBytes = sizeof(VertexData3DUnUV);
		}
		vertexBufferViews_.push_back(vertexBufferView);
	}
}

void Model::MapVertexData() {
	for (size_t i = 0; i < modelData_.meshes.size(); ++i) {
		if (modelData_.meshes[i].material.haveUV_) {
			VertexData3D* vertexData = nullptr;
			vertexResources_[i]->Map(0, nullptr, reinterpret_cast<void**>(&vertexData));
			std::memcpy(vertexData, modelData_.meshes[i].vertices.data(), sizeof(VertexData3D) * modelData_.meshes[i].vertices.size());
			vertexData_.push_back(vertexData);
		} else {
			VertexData3DUnUV* vertexDataUnUV = nullptr;
			vertexResources_[i]->Map(0, nullptr, reinterpret_cast<void**>(&vertexDataUnUV));
			std::memcpy(vertexDataUnUV, modelData_.meshes[i].verticesUnUV.data(), sizeof(VertexData3DUnUV) * modelData_.meshes[i].verticesUnUV.size());
			vertexDataUnUV_.push_back(vertexDataUnUV);
		}
	}
}

void Model::CreateIndexResource() {
	for (auto& mesh : modelData_.meshes) {
		Microsoft::WRL::ComPtr<ID3D12Resource> indexResource;
		if (mesh.material.haveUV_) {
			indexResource = SUGER::CreateBufferResource(sizeof(uint32_t) * mesh.indices.size());
		} else {
			// TODO::UVなしの処理
		}
		indexResources_.push_back(indexResource);
	}
}

void Model::CreateIndexBufferView() {
	for (size_t i = 0; i < modelData_.meshes.size(); ++i) {
		D3D12_INDEX_BUFFER_VIEW indexBufferView;
		indexBufferView.BufferLocation = indexResources_[i]->GetGPUVirtualAddress();
		if (modelData_.meshes[i].material.haveUV_) {
			indexBufferView.SizeInBytes = UINT(sizeof(uint32_t) * modelData_.meshes[i].indices.size());
			indexBufferView.Format = DXGI_FORMAT_R32_UINT;
		} else {
			// TODO::UVなしの処理
		}
		indexBufferViews_.push_back(indexBufferView);
	}
}

void Model::MapIndexData() {
	for (size_t i = 0; i < modelData_.meshes.size(); ++i) {
		if (modelData_.meshes[i].material.haveUV_) {
			uint32_t* indexData = nullptr;
			indexResources_[i]->Map(0, nullptr, reinterpret_cast<void**>(&indexData));
			std::memcpy(indexData, modelData_.meshes[i].indices.data(), sizeof(uint32_t) * modelData_.meshes[i].indices.size());
			indexData_.push_back(indexData);
		} else {
			// TODO::UVなしの処理
		}
	}

}

void Model::CreateMaterialResource() {
	for (size_t i = 0; i < materials_.size(); ++i) {
		Microsoft::WRL::ComPtr<ID3D12Resource> materialResource = SUGER::CreateBufferResource(sizeof(Material3D));
		materialResources_.push_back(materialResource);
	}
}

void Model::MapMaterialData() {
	for (size_t i = 0; i < materials_.size(); ++i) {
		Material3D* materialData = nullptr;
		materialResources_[i]->Map(0, nullptr, reinterpret_cast<void**>(&materialData));
		materialData->color = materials_[i].color;
		materialData->enbleLighting = materials_[i].enbleLighting;
		materialData->shininess = materials_[i].shininess;
		materialData->uvTransformMatrix = materials_[i].uvTransformMatrix;
		materialData_.push_back(materialData);
	}
}

Node Model::ReadNode(aiNode* node) {
	Node result;

	aiVector3D scale, translate;
	aiQuaternion rotate;

	node->mTransformation.Decompose(scale, rotate, translate);
	result.transform.scale = { scale.x,scale.y,scale.z };
	result.transform.rotate = { rotate.x,-rotate.y,-rotate.z,rotate.w };
	result.transform.translate = { -translate.x,translate.y,translate.z };

	result.localMatrix = MakeAffineMatrix(result.transform.scale, result.transform.rotate, result.transform.translate);

	result.name = node->mName.C_Str(); // node名を格納
	result.children.resize(node->mNumChildren);// 子供の数だけ確保
	for (uint32_t childIndex = 0; childIndex < node->mNumChildren; childIndex++) {
		// 再帰的に読んで階層構造を作っていく
		result.children[childIndex] = ReadNode(node->mChildren[childIndex]);
	}
	return result;
}

Animation Model::LoadAnimationFile(const std::string& filename, const std::string& directoryPath) {
	// アニメーションを入れる箱
	Animation animation;

	// 対応する拡張子のリスト
	std::vector<std::string> supportedExtensions = { ".gltf" };

	// ディレクトリ内のファイルを検索
	// モデルファイルが入っているディレクトリ
	std::string fileDirectoryPath = directoryPath + "/" + filename;
	// filesystem用
	std::filesystem::path modelDirectoryPath(fileDirectoryPath);

	// アニメーションのファイルパス
	std::string animationlFilePath;

	// ファイルの中身を検索
	for (const auto& entry : std::filesystem::directory_iterator(modelDirectoryPath)) {
		if (entry.is_regular_file()) {
			std::string ext = entry.path().extension().string();
			// 対応する拡張子かチェック
			if (std::find(supportedExtensions.begin(), supportedExtensions.end(), ext) != supportedExtensions.end()) {
				if (entry.path().stem().string() == filename) {
					animationlFilePath = entry.path().string();
					break;
				}
			}
		}
	}

	// ファイルが見つからなかった場合はエラー
	if (animationlFilePath.empty()) {
		std::cerr << "Error: Model file not found or unsupported format." << std::endl;
		return Animation();
	}

	// Assimpインポータ
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(animationlFilePath.c_str(), 0);
	assert(scene->mNumAnimations != 0);
	aiAnimation* animationAssimp = scene->mAnimations[0];
	animation.duration = float(animationAssimp->mDuration / animationAssimp->mTicksPerSecond);

	for (uint32_t channelIndex = 0; channelIndex < animationAssimp->mNumChannels; channelIndex++) {
		aiNodeAnim* nodeAnimationAssimp = animationAssimp->mChannels[channelIndex];
		NodeAnimation& nodeAnimation = animation.nodeAnimations[nodeAnimationAssimp->mNodeName.C_Str()];

		// Translation keys
		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumPositionKeys; keyIndex++) {
			aiVectorKey& keyAssimp = nodeAnimationAssimp->mPositionKeys[keyIndex];
			KeyframeVector3 keyframe;
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyframe.value = { -keyAssimp.mValue.x, keyAssimp.mValue.y, keyAssimp.mValue.z };
			nodeAnimation.translate.push_back(keyframe);
		}

		// Rotation keys
		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumRotationKeys; keyIndex++) {
			aiQuatKey& keyAssimp = nodeAnimationAssimp->mRotationKeys[keyIndex];
			KeyframeQuaternion keyframe;
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyframe.value = { keyAssimp.mValue.x, -keyAssimp.mValue.y, -keyAssimp.mValue.z, keyAssimp.mValue.w };
			nodeAnimation.rotate.push_back(keyframe);
		}

		// Scaling keys
		for (uint32_t keyIndex = 0; keyIndex < nodeAnimationAssimp->mNumScalingKeys; keyIndex++) {
			aiVectorKey& keyAssimp = nodeAnimationAssimp->mScalingKeys[keyIndex];
			KeyframeVector3 keyframe;
			keyframe.time = float(keyAssimp.mTime / animationAssimp->mTicksPerSecond);
			keyframe.value = { keyAssimp.mValue.x, keyAssimp.mValue.y, keyAssimp.mValue.z };
			nodeAnimation.scale.push_back(keyframe);
		}
	}

	return animation;
}

Vector3 Model::CalculateVelue(const std::vector<KeyframeVector3>& keyframes, float time) {
	assert(!keyframes.empty());

	if (keyframes.size() == 1 || time <= keyframes[0].time) {
		return keyframes[0].value;
	}

	for (size_t index = 0; index < keyframes.size() - 1; ++index) {
		size_t nextIndex = index + 1;
		// indexとnextIndexの2つのKeyframeを取得して範囲内に時刻があるかを判定
		if (keyframes[index].time <= time && time <= keyframes[nextIndex].time) {
			// 範囲内を補完する
			float t = (time - keyframes[index].time) / (keyframes[nextIndex].time - keyframes[index].time);
			return Lerp(keyframes[index].value, keyframes[nextIndex].value, t);
		}
	}

	return (*keyframes.rbegin()).value;
}

Quaternion Model::CalculateValue(const std::vector<KeyframeQuaternion>& keyframes, float time) {
	assert(!keyframes.empty());

	if (keyframes.size() == 1 || time <= keyframes[0].time) {
		return keyframes[0].value;
	}

	for (size_t index = 0; index < keyframes.size() - 1; ++index) {
		size_t nextIndex = index + 1;
		// indexとnextIndexの2つのKeyframeを取得して範囲内に時刻があるかを判定
		if (keyframes[index].time <= time && time <= keyframes[nextIndex].time) {
			// 範囲内を補完する
			float t = (time - keyframes[index].time) / (keyframes[nextIndex].time - keyframes[index].time);
			return Slerp(keyframes[index].value, keyframes[nextIndex].value, t);
		}
	}

	return (*keyframes.rbegin()).value;
}

void Model::ApplyAnimation(Skeleton& skeleton, const Animation& animation, float animationTime) {
	for (Joint& joint : skeleton.joints) {
		if (auto it = animation.nodeAnimations.find(joint.name); it != animation.nodeAnimations.end()) {
			const NodeAnimation& rootNodeAnimation = (*it).second;
			joint.transform.translate = CalculateVelue(rootNodeAnimation.translate, animationTime);
			joint.transform.rotate = CalculateValue(rootNodeAnimation.rotate, animationTime);
			joint.transform.scale = CalculateVelue(rootNodeAnimation.scale, animationTime);
		}
	}
}

Skeleton Model::CreateSkeleton(const Node& rootNode) {
	Skeleton skeleton;
	skeleton.root = CreateJoint(rootNode, {}, skeleton.joints);

	for (const Joint& joint : skeleton.joints) {
		skeleton.jointMap.emplace(joint.name, joint.index);
	}

	return skeleton;
}

void Model::SkeletonUpdate(Skeleton& skeleton) {
	for (Joint& joint : skeleton.joints) {
		joint.loclMatrix = MakeAffineMatrix(joint.transform.scale, joint.transform.rotate, joint.transform.translate);
		if (joint.parent) {
			joint.skeletonSpaceMatrix = joint.loclMatrix * skeleton.joints[*joint.parent].skeletonSpaceMatrix;
		} else {
			joint.skeletonSpaceMatrix = joint.loclMatrix;
		}
	}
}

int32_t Model::CreateJoint(const Node& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints) {
	Joint joint;
	joint.name = node.name;
	joint.loclMatrix = node.localMatrix;
	joint.skeletonSpaceMatrix = MakeIdentityMatrix4x4();
	joint.transform = node.transform;
	joint.index = int32_t(joints.size());
	joint.parent = parent;
	joints.push_back(joint);
	for (const Node& child : node.children) {
		int32_t childIndex = CreateJoint(child, joint.index, joints);
		joints[joint.index].children.push_back(childIndex);
	}
	return joint.index;
}

SkinCluster Model::CreateSkinCluster(const Skeleton& skeleton, const ModelData& modelData) {
	SkinCluster skinCluster;
	// palette用のリソースを確保
	skinCluster.paletteResources = SUGER::CreateBufferResource(sizeof(WellForGPU) * skeleton.jointMap.size());
	WellForGPU* mappedPalette = nullptr;
	skinCluster.paletteResources->Map(0, nullptr, reinterpret_cast<void**>(&mappedPalette));
	skinCluster.mappedPalette = { mappedPalette, skeleton.joints.size() };

	// srvのインデックスを割り当て
	skinClusterSrvIndex_ = SUGER::SrvAllocate();

	// Srvを作成
	SUGER::CreateSrvStructured(skinClusterSrvIndex_, skinCluster.paletteResources.Get(), UINT(skeleton.joints.size()), sizeof(WellForGPU));

	// 合計頂点数を取得
	size_t totalVertexCount = 0;
	for (const auto& mesh : modelData.meshes) {
		totalVertexCount += mesh.vertices.size();
	}

	// influence用のリソースを確保
	skinCluster.influenceResource = SUGER::CreateBufferResource(sizeof(VertexInfluence) * totalVertexCount);
	VertexInfluence* mappedInfluence = nullptr;
	skinCluster.influenceResource->Map(0, nullptr, reinterpret_cast<void**>(&mappedInfluence));
	std::memset(mappedInfluence, 0, sizeof(VertexInfluence) * totalVertexCount);
	skinCluster.mappedInfluence = { mappedInfluence,totalVertexCount };

	// Influence用のVBVを作成
	skinCluster.influenceBufferView.BufferLocation = skinCluster.influenceResource->GetGPUVirtualAddress();
	skinCluster.influenceBufferView.SizeInBytes = UINT(sizeof(VertexInfluence) * totalVertexCount);
	skinCluster.influenceBufferView.StrideInBytes = sizeof(VertexInfluence);

	// InverseBindPoseMatrixの保存領域を作成
	skinCluster.inverseBindPoseMatrices.resize(skeleton.joints.size());
	for (size_t i = 0; i < skeleton.joints.size(); ++i) {
		skinCluster.inverseBindPoseMatrices[i] = MakeIdentityMatrix4x4();
	}


	// ModelDataのskinCluster情報を解析してInfluenceの中身を埋める
	for (const auto& jointWeight : modelData.skinClusterData) {
		auto it = skeleton.jointMap.find(jointWeight.first);
		if (it == skeleton.jointMap.end()) {
			continue;
		}

		skinCluster.inverseBindPoseMatrices[(*it).second] = jointWeight.second.inverseBindPoseMatrix;
		for (const auto& vertexWeight : jointWeight.second.vertexWeights) {
			auto& currentInfluence = skinCluster.mappedInfluence[vertexWeight.vertexIndex];
			for (uint32_t index = 0; index < kNumMaxInfluence; index++) {
				if (currentInfluence.weights[index] == 0.0f) {
					currentInfluence.weights[index] = vertexWeight.weight;
					currentInfluence.jointindices[index] = (*it).second;
					break;
				}
			}
		}

	}


	return skinCluster;

}

void Model::SkinClusterUpdate(SkinCluster& skinCluster, const Skeleton& skeleton) {
	for (size_t jointIndex = 0; jointIndex < skeleton.joints.size(); ++jointIndex) {
		assert(jointIndex < skinCluster.inverseBindPoseMatrices.size());
		skinCluster.mappedPalette[jointIndex].skeletonSpaceMatrix =
			skinCluster.inverseBindPoseMatrices[jointIndex] * skeleton.joints[jointIndex].skeletonSpaceMatrix;
		skinCluster.mappedPalette[jointIndex].skeletonSpaceInverseTransposeMatrix =
			Transpose(Inverse(skinCluster.mappedPalette[jointIndex].skeletonSpaceMatrix));
	}
}
