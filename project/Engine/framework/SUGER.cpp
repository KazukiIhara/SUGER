#include "SUGER.h"

#include "debugTools/logger/Logger.h"
#include "input/direct/DirectInput.h"

#include "manager/window/WindowManager.h"
#include "manager/directX/DirectXManager.h"
#include "manager/srv/SRVManager.h"
#include "manager/imgui/ImGuiManager.h"
#include "manager/texture/TextureManager.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"
#include "iScene/abstractFactory/AbstractSceneFactory.h"
#include "manager/model/ModelManager.h"
#include "manager/object/2d/Object2DManager.h"
#include "manager/object/3d/Object3DManager.h"
#include "manager/particle/ParticleManager.h"
#include "2d/system/Object2dSystem.h"
#include "3d/system/Object3dSystem.h"
#include "particle/system/ParticleSystem.h"

#ifdef _DEBUG
#include "debugTools/leakChecker/d3dResource/D3DResourceLeakChecker.h"
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
std::unique_ptr<Object3DManager> SUGER::object3dManager_ = nullptr;
std::unique_ptr<ParticleManager> SUGER::particleManager_ = nullptr;
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

	// object3dManagerの初期化
	object3dManager_ = std::make_unique<Object3DManager>();
	object3dManager_->Initialize(modelManager_.get());

	// object2dManagerの初期化
	object2dManager_ = std::make_unique<Object2DManager>();
	object2dManager_->Initialize();

	// particleManagerの初期化
	particleManager_ = std::make_unique<ParticleManager>();
	particleManager_->Initialize(modelManager_.get());

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

	// ParticleManagerの終了処理
	if (particleManager_) {
		particleManager_.reset();
	}

	// Object2DManagerの終了処理
	if (object2dManager_) {
		object2dManager_->Finalize();
		object2dManager_.reset();
	}

	// Object3DManagerの終了処理
	if (object3dManager_) {
		object3dManager_->Finalize();
		object3dManager_.reset();
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

	// 入力の更新
	directInput_->Update();

	// escキーで終了
	if (directInput_->PushKey(DIK_ESCAPE)) {
		endRequest_ = true;
	}

	// ImGui開始処理
	imguiManager_->BeginFrame();

	// FPS表示
	ShowFPS();

}

void SUGER::Draw() {
	// 3Dオブジェクト描画前処理
	PreDrawObject3D();
	// 3Dオブジェクト描画処理
	Draw3DObjects();

	// 3Dパーティクル描画前処理
	PreDrawParticle3D();
	// 3Dパーティクル描画処理
	DrawParticle();

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

void SUGER::CreateSrvInstancing(uint32_t srvIndex, ID3D12Resource* pResource, uint32_t numElements, UINT structureByteStride) {
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

void SUGER::Create2DObject(const std::string& name, const std::string& filePath) {
	object2dManager_->Create(name, filePath);
}

void SUGER::Update2DObjects() {
	object2dManager_->Update();
}

void SUGER::Draw2DObjects() {
	object2dManager_->Draw();
}

void SUGER::Create3DObject(const std::string& name, const std::string& filePath, const Transform3D& transform) {
	object3dManager_->Create(name, filePath, transform);
}

void SUGER::Update3DObjects() {
	object3dManager_->Update();
}

void SUGER::Draw3DObjects() {
	object3dManager_->Draw();
}

Object3D* SUGER::FindObject3D(const std::string& name) {
	return object3dManager_->Find(name);
}

void SUGER::SetRequiredObjects(Camera* camera, PunctualLight* punctualLight) {
	object3dManager_->SetRequiredObjects(camera, punctualLight);
	particleManager_->SetSceneCamera(camera);
}

void SUGER::SetSceneCamera(Camera* camera) {
	object3dManager_->SetSceneCamera(camera);
	particleManager_->SetSceneCamera(camera);
}

void SUGER::CreatePlaneParticle(const std::string& name, const std::string& filePath) {
	particleManager_->CreatePlane(name, filePath);
}

void SUGER::UpdateParticle() {
	particleManager_->Update();
}

void SUGER::DrawParticle() {
	particleManager_->Draw();
}

void SUGER::PreDrawObject2D() {
	object2dSystem_->PreDraw();
}

void SUGER::PreDrawObject3D() {
	object3dSystem_->PreDraw();
}

void SUGER::PreDrawParticle3D() {
	particleSystem_->PreDraw();
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
