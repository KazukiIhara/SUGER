#include "SUGER.h"

#include "debugTools/logger/Logger.h"

#ifdef _DEBUG
std::unique_ptr<D3DResourceLeakChecker> SUGER::leakCheck_ = nullptr;
#endif // _DEBUG

// Staticメンバ変数の初期化
std::unique_ptr<WindowManager> SUGER::windowManager_ = nullptr;
std::unique_ptr<DirectInput> SUGER::directInput_ = nullptr;
std::unique_ptr<DirectXManager> SUGER::directXManager_ = nullptr;
std::unique_ptr<SRVManager> SUGER::srvManager_ = nullptr;
std::unique_ptr<ImGuiManager> SUGER::imguiManager_ = nullptr;
std::unique_ptr<TextureManager> SUGER::textureManager_ = nullptr;
std::unique_ptr<GraphicsPipelineManager> SUGER::graphicsPipelineManager_ = nullptr;
std::unique_ptr<ModelManager> SUGER::modelManager_ = nullptr;
std::unique_ptr<Object2DManager> SUGER::object2dManager_ = nullptr;
std::unique_ptr<EmptyManager> SUGER::emptyManager_ = nullptr;
std::unique_ptr<EntityManager> SUGER::entityManager_ = nullptr;
std::unique_ptr<EmitterManager> SUGER::emitterManager_ = nullptr;
std::unique_ptr<ParticleManager> SUGER::particleManager_ = nullptr;
std::unique_ptr<SoundManager> SUGER::soundManager_ = nullptr;
std::unique_ptr<JsonLevelDataManager> SUGER::jsonLevelDataManager_ = nullptr;
std::unique_ptr<GrobalDataManager> SUGER::grobalDataManager_ = nullptr;
std::unique_ptr<Object2DSystem> SUGER::object2dSystem_ = nullptr;
std::unique_ptr<Object3DSystem> SUGER::object3dSystem_ = nullptr;
std::unique_ptr<ParticleSystem> SUGER::particleSystem_ = nullptr;


void SUGER::Initialize() {
	Logger::Log("SUGER,Initialize\n");

	// WindowManagerの初期化
	windowManager_ = std::make_unique<WindowManager>();
	windowManager_->Initialize();

	// DirectInputの初期化
	directInput_ = std::make_unique<DirectInput>();
	directInput_->Initialize(windowManager_.get());

	// DirectXManagerの初期化
	directXManager_ = std::make_unique<DirectXManager>();
	directXManager_->Initialize(windowManager_.get());

	// SRVManagerの初期化
	srvManager_ = std::make_unique<SRVManager>();
	srvManager_->Initialize(directXManager_.get());

	// ImGuiManagerの初期化
	imguiManager_ = std::make_unique<ImGuiManager>();
	imguiManager_->Initialize(windowManager_.get(), directXManager_.get(), srvManager_.get());

	// TextureManagerの初期化
	textureManager_ = std::make_unique<TextureManager>();
	textureManager_->Initialize(directXManager_.get(), srvManager_.get());

	// GraphicsPipelineManagerの初期化
	graphicsPipelineManager_ = std::make_unique<GraphicsPipelineManager>();
	graphicsPipelineManager_->Initialize(directXManager_.get());

	// ModelManagerの初期化
	modelManager_ = std::make_unique<ModelManager>();
	modelManager_->Initialize();

	// object2dManagerの初期化
	object2dManager_ = std::make_unique<Object2DManager>();
	object2dManager_->Initialize();

	// emptyManagerの初期化
	emptyManager_ = std::make_unique<EmptyManager>();
	emptyManager_->Initialize();

	// entityManagerの初期化
	entityManager_ = std::make_unique<EntityManager>();
	entityManager_->Initialize(modelManager_.get());

	// emitterManagerの初期化
	emitterManager_ = std::make_unique<EmitterManager>();
	emitterManager_->Initialize();

	// FixParticleManagerの初期化
	particleManager_ = std::make_unique<ParticleManager>();
	particleManager_->Initialize(modelManager_.get(), textureManager_.get());



	// soundManagerの初期化
	soundManager_ = std::make_unique<SoundManager>();
	soundManager_->Initialize();

	// JsonLevelDataManagerの初期化
	jsonLevelDataManager_ = std::make_unique<JsonLevelDataManager>();
	jsonLevelDataManager_->Initialize();

	// grobalDataManagerの初期化
	grobalDataManager_ = std::make_unique<GrobalDataManager>();
	grobalDataManager_->Initialize(directXManager_.get());

	// Object2DSystemの初期化
	object2dSystem_ = std::make_unique<Object2DSystem>();
	object2dSystem_->Initialize(directXManager_.get(), graphicsPipelineManager_.get());

	// Object3DSystemの初期化
	object3dSystem_ = std::make_unique<Object3DSystem>();
	object3dSystem_->Initialize(directXManager_.get(), graphicsPipelineManager_.get());

	// ParticleSystemの初期化
	particleSystem_ = std::make_unique<ParticleSystem>();
	particleSystem_->Initialize(directXManager_.get(), graphicsPipelineManager_.get());
}

void SUGER::Finalize() {
	Logger::Log("SUGER,Finalized\n");

	// 各オブジェクトの終了処理を生成した順番とは逆に行う

	// ParticleSystemの終了処理
	if (particleSystem_) {
		particleSystem_.reset();
	}

	// Object3DSystemの終了処理
	if (object3dSystem_) {
		object3dSystem_.reset();
	}

	// Object2DSystemの終了処理
	if (object2dSystem_) {
		object2dSystem_.reset();
	}

	// grobalDataManagerの終了処理
	if (grobalDataManager_) {
		grobalDataManager_->Finalize();
		grobalDataManager_.reset();
	}

	// JsonLevelDataManagerの終了処理
	if (jsonLevelDataManager_) {
		jsonLevelDataManager_->Finalize();
		jsonLevelDataManager_.reset();
	}

	// soundManagerの終了処理
	if (soundManager_) {
		soundManager_->Finalize();
		soundManager_.reset();
	}

	// emitterManagerの終了処理
	if (emitterManager_) {
		emitterManager_->Finalize();
		emitterManager_.reset();
	}

	// FixParticleManagerの終了処理
	if (particleManager_) {
		particleManager_->Finalize();
		particleManager_.reset();
	}

	// Object2DManagerの終了処理
	if (object2dManager_) {
		object2dManager_->Finalize();
		object2dManager_.reset();
	}

	// EmptyManagerの終了処理
	if (emptyManager_) {
		emptyManager_->Finalize();
		emptyManager_.reset();
	}

	// EntityManagerの終了処理
	if (entityManager_) {
		entityManager_->Finalize();
		entityManager_.reset();
	}

	// ModelManagerの終了処理
	if (modelManager_) {
		modelManager_.reset();
	}

	// GraphicsPipelineManagerの終了処理
	if (graphicsPipelineManager_) {
		graphicsPipelineManager_.reset();
	}

	// TextureManagerの終了処理
	if (textureManager_) {
		textureManager_.reset();
	}

	// ImGuiManagerの終了処理
	if (imguiManager_) {
		imguiManager_->Finalize();
		imguiManager_.reset();
	}

	// SRVManagerの終了処理
	if (srvManager_) {
		srvManager_.reset();
	}

	// DirectXManagerの終了処理
	if (directXManager_) {
		directXManager_.reset();
	}

	// DirectInputの終了処理
	if (directInput_) {
		directInput_.reset();
	}

	// WindowManagerの終了処理
	if (windowManager_) {
		windowManager_->Finalize();
		windowManager_.reset();
	}
}

void SUGER::Update() {

	// ウィンドウにメッセージが来ていたら最優先で処理
	if (windowManager_->ProcessMessage()) {
		endRequest_ = true;
	}


	// F11キーでフルスクリーン切り替え処理
	if (directInput_->TriggerKey(DIK_F11)) {
		windowManager_->ToggleFullScreen();
	}

	// 入力の更新
	directInput_->Update();

	// escキーで終了
	if (directInput_->PushKey(DIK_ESCAPE)) {
		endRequest_ = true;
	}

	// ImGui開始処理
	imguiManager_->BeginFrame();

	// グローバルデータ更新処理
	grobalDataManager_->Update();

	// FPS表示
	ShowFPS();

}

void SUGER::Draw() {
	// 3Dオブジェクト描画前処理
	PreDrawObject3D();
	// Entity描画処理
	DrawEntiteis();

	// Skinningあり3Dオブジェクト描画前処理
	PreDrawObject3DSkinning();
	// Skining付きEntity描画処理
	DrawSkiningEntities();

	// 3Dパーティクル描画前処理
	PreDrawParticle3D();
	// 3Dパーティクル描画処理
	DrawParticles();

	// 2Dオブジェクト描画前処理
	PreDrawObject2D();
	// 2Dオブジェクト描画処理
	Draw2DObjects();

}

void SUGER::Run() {
	// 初期化
	Initialize();
	// メインループ
	while (true) {
		// 更新
		Update();

		// 終了リクエストがあったらループを抜ける;
		if (IsEndRequest()) {
			break;
		}

		// 描画
		Draw();
	}

	// 終了
	Finalize();
}

void SUGER::PreDraw() {
	// ImGui内部コマンド生成
	imguiManager_->EndFrame();
	// DirectX描画前処理
	directXManager_->PreDraw();
	// SrvManager描画前処理
	srvManager_->PreDraw();
}

void SUGER::PostDraw() {
	// ImGui描画処理
	imguiManager_->Draw();
	// DirectX描画後処理
	directXManager_->PostDraw();
}

bool SUGER::PushKey(BYTE keyNumber) {
	return directInput_->PushKey(keyNumber);
}

bool SUGER::TriggerKey(BYTE keyNumber) {
	return directInput_->TriggerKey(keyNumber);
}

bool SUGER::HoldKey(BYTE keyNumber) {
	return directInput_->HoldKey(keyNumber);
}

bool SUGER::ReleaseKey(BYTE keyNumber) {
	return directInput_->ReleaseKey(keyNumber);
}

bool SUGER::PushButton(int controllerID, int buttonNumber) {
	return directInput_->PushButton(controllerID, buttonNumber);
}

bool SUGER::TriggerButton(int controllerID, int buttonNumber) {
	return directInput_->TriggerButton(controllerID, buttonNumber);
}

bool SUGER::HoldButton(int controllerID, int buttonNumber) {
	return directInput_->HoldButton(controllerID, buttonNumber);
}

bool SUGER::ReleaseButton(int controllerID, int buttonNumber) {
	return directInput_->ReleaseButton(controllerID, buttonNumber);
}

int SUGER::GetLeftStickX(int controllerID) {
	return directInput_->GetLeftStickX(controllerID);
}

int SUGER::GetLeftStickY(int controllerID) {
	return directInput_->GetLeftStickY(controllerID);
}

int SUGER::GetRightStickX(int controllerID) {
	return directInput_->GetRightStickX(controllerID);
}

int SUGER::GetRightStickY(int controllerID) {
	return directInput_->GetRightStickY(controllerID);
}

bool SUGER::IsPadUp(int controllerID) {
	return directInput_->IsPadUp(controllerID);
}

bool SUGER::IsPadRight(int controllerID) {
	return directInput_->IsPadRight(controllerID);
}

bool SUGER::IsPadDown(int controllerID) {
	return directInput_->IsPadDown(controllerID);
}

bool SUGER::IsPadLeft(int controllerID) {
	return directInput_->IsPadLeft(controllerID);
}


ID3D12Device* SUGER::GetDirectXDevice() {
	return directXManager_->GetDevice();
}

ID3D12GraphicsCommandList* SUGER::GetDirectXCommandList() {
	return directXManager_->GetCommandList();
}

ComPtr<ID3D12Resource> SUGER::CreateBufferResource(size_t sizeInBytes) {
	return directXManager_->CreateBufferResource(sizeInBytes);
}

D3D12_CPU_DESCRIPTOR_HANDLE SUGER::GetSRVDescriptorHandleCPU(uint32_t index) {
	return srvManager_->GetDescriptorHandleCPU(index);
}

D3D12_GPU_DESCRIPTOR_HANDLE SUGER::GetSRVDescriptorHandleGPU(uint32_t index) {
	return srvManager_->GetDescriptorHandleGPU(index);
}

void SUGER::SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t srvIndex) {
	srvManager_->SetGraphicsRootDescriptorTable(rootParameterIndex, srvIndex);
}

uint32_t SUGER::SrvAllocate() {
	return srvManager_->Allocate();
}

void SUGER::CreateSrvStructured(uint32_t srvIndex, ID3D12Resource* pResource, uint32_t numElements, UINT structureByteStride) {
	srvManager_->CreateSrvStructuredBuffer(srvIndex, pResource, numElements, structureByteStride);
}

void SUGER::LoadTexture(const std::string& filePath) {
	textureManager_->Load(filePath);
}

std::unordered_map<std::string, Texture>& SUGER::GetTexture() {
	return textureManager_->GetTexture();
}

const DirectX::TexMetadata& SUGER::GetTextureMetaData(const std::string& filePath) {
	return textureManager_->GetMetaData(filePath);
}

ID3D12PipelineState* SUGER::GetPipelineState(PipelineState pipelineState, BlendMode blendMode) {
	return graphicsPipelineManager_->GetPipelineState(pipelineState, blendMode);
}

void SUGER::LoadModel(const std::string& filePath) {
	modelManager_->Load(filePath);
}

void SUGER::CreateSphere(const std::string& textureFilePath) {
	modelManager_->CreateSphere(textureFilePath);
}

Model* SUGER::FindModel(const std::string& filePath) {
	return modelManager_->Find(filePath);
}

std::string SUGER::Create2DObject(const std::string& name, const std::string& filePath) {
	return object2dManager_->Create(name, filePath);
}

void SUGER::Update2DObjects() {
	object2dManager_->Update();
}

void SUGER::Draw2DObjects() {
	object2dManager_->Draw();
}

Sprite* SUGER::FindObject2D(const std::string& name) {
	return object2dManager_->Find(name);
}

std::string SUGER::CreateEmpty(const std::string& name, const EulerTransform3D& transform) {
	return emptyManager_->Create(name, transform);
}

void SUGER::UpdateEmpties() {
	emptyManager_->Update();
}

Empty* SUGER::FindEmpty(const std::string& name) {
	return emptyManager_->Find(name);
}

std::string SUGER::CreateEntity(const std::string& name, const std::string& filePath, const EulerTransform3D& transform) {
	return entityManager_->Create(name, filePath, transform);
}

void SUGER::UpdateEntities() {
	entityManager_->Update();
}

void SUGER::DrawEntiteis() {
	entityManager_->Draw();
}

void SUGER::DrawSkiningEntities() {
	entityManager_->DrawSkining();
}

Entity* SUGER::FindEntity(const std::string& name) {
	return entityManager_->Find(name);
}

void SUGER::SetRequiredObjects(Camera* camera, PunctualLight* punctualLight) {
	entityManager_->SetRequiredObjects(camera, punctualLight);
	particleManager_->SetSceneCamera(camera);
}

void SUGER::SetSceneCamera(Camera* camera) {
	entityManager_->SetSceneCamera(camera);
	particleManager_->SetSceneCamera(camera);
}

void SUGER::CreateEmitter(const std::string& name, const EulerTransform3D& transform) {
	emitterManager_->CreateEmitter(name, transform);
}

void SUGER::UpdateEmitters() {
	emitterManager_->Update();
}

Emitter* SUGER::FindEmitter(const std::string& name) {
	return emitterManager_->Find(name);
}

void SUGER::CreateFixParticle(const std::string& name, const ParticleType& particleType, const std::string& filePath) {
	// 既定のディレクトリパス
	const std::string& textureDirectoryPath = "resources/images/";
	// パーティクルタイプに応じてパーティクルを作成
	switch (particleType) {
		case kPlane:
			// 板ポリパーティクルを作成
			particleManager_->CreatePlaneParticle(name, textureDirectoryPath + filePath);
			break;
		case kModel:
			// モデルパーティクルを作成
			particleManager_->CreateModelParticle(name, filePath);
			break;
	}

}

void SUGER::UpdateParticles() {
	particleManager_->Update();
}

void SUGER::DrawParticles() {
	particleManager_->Draw();
}

Particle* SUGER::FindFixParticle(const std::string& name) {
	return particleManager_->Find(name);
}

void SUGER::LoadWaveSound(const std::string& filename, const std::string& directoryPath) {
	soundManager_->LoadWave(filename, directoryPath);
}

void SUGER::PlayWaveSound(const std::string& filename) {
	soundManager_->PlayWave(filename);
}

void SUGER::PreDrawObject2D() {
	object2dSystem_->PreDraw();
}

void SUGER::PreDrawObject3D() {
	object3dSystem_->PreDraw();
}

void SUGER::PreDrawObject3DSkinning() {
	object3dSystem_->PreDrawSkinning();
}

void SUGER::PreDrawParticle3D() {
	particleSystem_->PreDraw();
}

void SUGER::LoadJsonLevelData(const std::string& fileName) {
	jsonLevelDataManager_->Load(fileName);
}

JsonLevelData* SUGER::FindJsonLevelData(const std::string& levelDataName) {
	return jsonLevelDataManager_->Find(levelDataName);
}

void SUGER::AddGrobalDataGroup(const std::string& groupname) {
	grobalDataManager_->CreateGroup(groupname);
}

void SUGER::AddGrobalDataItem(const std::string& groupname, const std::string& itemname, int32_t value) {
	grobalDataManager_->AddItem(groupname, itemname, value);
}

void SUGER::AddGrobalDataItem(const std::string& groupname, const std::string& itemname, float value) {
	grobalDataManager_->AddItem(groupname, itemname, value);
}

void SUGER::AddGrobalDataItem(const std::string& groupname, const std::string& itemname, Vector3 value) {
	grobalDataManager_->AddItem(groupname, itemname, value);
}

void SUGER::AddGrobalDataItem(const std::string& groupname, const std::string& itemname, bool value) {
	grobalDataManager_->AddItem(groupname, itemname, value);
}

void SUGER::SetGrobalDataValue(const std::string& groupname, const std::string& itemname, int32_t value) {
	grobalDataManager_->SetValue(groupname, itemname, value);
}

void SUGER::SetGrobalDataValue(const std::string& groupname, const std::string& itemname, float value) {
	grobalDataManager_->SetValue(groupname, itemname, value);
}

void SUGER::SetGrobalDataValue(const std::string& groupname, const std::string& itemname, Vector3 value) {
	grobalDataManager_->SetValue(groupname, itemname, value);
}

void SUGER::SetGrobalDataValue(const std::string& groupname, const std::string& itemname, bool value) {
	grobalDataManager_->SetValue(groupname, itemname, value);
}

int32_t SUGER::GetGrobalDataValueInt(const std::string& groupName, const std::string& key) {
	return grobalDataManager_->GetValueInt(groupName, key);
}

float SUGER::GetGrobalDataValueFloat(const std::string& groupName, const std::string& key) {
	return grobalDataManager_->GetValueFloat(groupName, key);
}

Vector3 SUGER::GetGrobalDataValueVector3(const std::string& groupName, const std::string& key) {
	return grobalDataManager_->GetValueVector3(groupName, key);
}

bool SUGER::GetGrobalDataValueBool(const std::string& groupName, const std::string& key) {
	return grobalDataManager_->GetValueBool(groupName, key);
}

void SUGER::ShowFPS() {
#ifdef _DEBUG
	// フレームレート表示の設定
	ImGuiIO& io = ImGui::GetIO();

	// 左上に固定
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowBgAlpha(0.0f); // 背景を透明にする

	// ウィンドウを作成せずに、文字だけを描画
	ImGui::Begin("FPS Overlay", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoTitleBar);

	// 文字色を緑に変更
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 255, 0, 255)); // 緑色
	ImGui::Text("FPS: %.1f", io.Framerate);
	ImGui::PopStyleColor();

	ImGui::End();
#endif // _DEBUG
}
