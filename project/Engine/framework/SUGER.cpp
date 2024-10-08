#include "SUGER.h"

#include "debugTools/logger/Logger.h"
#include "input/direct/DirectInput.h"

#include "manager/window/WindowManager.h"
#include "manager/directX/DirectXManager.h"
#include "manager/srv/SRVManager.h"
#include "manager/imgui/ImGuiManager.h"
#include "manager/texture/TextureManager.h"
#include "manager/pipeline/graphics/GraphicsPipelineManager.h"

#include "2d/system/Object2dSystem.h"

// Staticメンバ変数の初期化
std::unique_ptr<WindowManager> SUGER::windowManager_ = nullptr;
std::unique_ptr<DirectInput> SUGER::directInput_ = nullptr;
std::unique_ptr<DirectXManager> SUGER::directXManager_ = nullptr;
std::unique_ptr<SRVManager> SUGER::srvManager_ = nullptr;
std::unique_ptr<ImGuiManager> SUGER::imguiManager_ = nullptr;
std::unique_ptr<TextureManager> SUGER::textureManager_ = nullptr;
std::unique_ptr<GraphicsPipelineManager> SUGER::graphicsPipelineManager_ = nullptr;
std::unique_ptr<Object2DSystem> SUGER::object2dSystem_ = nullptr;
std::unique_ptr<AbstractSceneFactory> SUGER::sceneFactory_ = nullptr;

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

	// Object2DSystemの初期化
	object2dSystem_ = std::make_unique<Object2DSystem>();
	object2dSystem_->Initialize(directXManager_.get(), graphicsPipelineManager_.get());

}

void SUGER::Finalize() {
	Logger::Log("SUGER,Finalized\n");

	

	imguiManager_->Finalize();

	windowManager_->Finalize();
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

void SUGER::PreDrawObject2D() {
	object2dSystem_->PreDraw();
}
