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
#include "2d/system/Object2dSystem.h"
#include "3d/system/Object3dSystem.h"

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
std::unique_ptr<Object2DSystem> SUGER::object2dSystem_ = nullptr;
std::unique_ptr<Object3DSystem> SUGER::object3dSystem_ = nullptr;

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

	// Object2DSystemの初期化
	object2dSystem_ = std::make_unique<Object2DSystem>();
	object2dSystem_->Initialize(directXManager_.get(), graphicsPipelineManager_.get());

	// Object3DSystemの初期化
	object3dSystem_ = std::make_unique<Object3DSystem>();
	object3dSystem_->Initialize(directXManager_.get(), graphicsPipelineManager_.get());
}

void SUGER::Finalize() {
	Logger::Log("SUGER,Finalized\n");

	// 各オブジェクトの終了処理を生成した順番とは逆に行う

	// Object2DSystemの終了処理
	if (object2dSystem_) {
		object2dSystem_.reset();
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

#ifdef _DEBUG
	ImGui::Begin("SUGER Update");
	ImGui::Text("framelate %f", ImGui::GetIO().Framerate);
	ImGui::End();
#endif // _DEBUG
}

void SUGER::Draw() {}

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

void SUGER::SetGraphicsRootDescriptorTable(UINT rootParameterIndex, uint32_t srvIndex) {
	srvManager_->SetGraphicsRootDescriptorTable(rootParameterIndex, srvIndex);
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

void SUGER::PreDrawObject2D() {
	object2dSystem_->PreDraw();
}

void SUGER::PreDrawObject3D() {
	object3dSystem_->PreDraw();
}
