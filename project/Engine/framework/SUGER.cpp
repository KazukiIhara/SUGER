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
#include "2d/system/Object2dSystem.h"

// Staticメンバ変数の初期化
WindowManager* SUGER::windowManager_ = nullptr;
DirectInput* SUGER::directInput_ = nullptr;
DirectXManager* SUGER::directXManager_ = nullptr;
SRVManager* SUGER::srvManager_ = nullptr;
ImGuiManager* SUGER::imguiManager_ = nullptr;
TextureManager* SUGER::textureManager_ = nullptr;
GraphicsPipelineManager* SUGER::graphicsPipelineManager_ = nullptr;
Object2DSystem* SUGER::object2dSystem_ = nullptr;
AbstractSceneFactory* SUGER::sceneFactory_ = nullptr;

void SUGER::Initialize() {
	Logger::Log("SUGER,Initialize\n");

	// WindowManagerの初期化
	windowManager_ = new WindowManager();
	windowManager_->Initialize();

	// DirectInputの初期化
	directInput_ = new DirectInput();
	directInput_->Initialize(windowManager_);

	// DirectXManagerの初期化
	directXManager_ = new DirectXManager();
	directXManager_->Initialize(windowManager_);

	// SRVManagerの初期化
	srvManager_ = new SRVManager();
	srvManager_->Initialize(directXManager_);

	// ImGuiManagerの初期化
	imguiManager_ = new ImGuiManager();
	imguiManager_->Initialize(windowManager_, directXManager_, srvManager_);

	// TextureManagerの初期化
	textureManager_ = new TextureManager();
	textureManager_->Initialize(directXManager_, srvManager_);

	// GraphicsPipelineManagerの初期化
	graphicsPipelineManager_ = new GraphicsPipelineManager();
	graphicsPipelineManager_->Initialize(directXManager_);

	// Object2DSystemの初期化
	object2dSystem_ = new Object2DSystem();
	object2dSystem_->Initialize(directXManager_, graphicsPipelineManager_);
}

void SUGER::Finalize() {
	Logger::Log("SUGER,Finalized\n");

	// 各オブジェクトの終了処理とメモリ解放
	delete sceneFactory_;
	sceneFactory_ = nullptr;

	delete object2dSystem_;
	object2dSystem_ = nullptr;

	delete graphicsPipelineManager_;
	graphicsPipelineManager_ = nullptr;

	delete textureManager_;
	textureManager_ = nullptr;

	delete srvManager_;
	srvManager_ = nullptr;

	if (imguiManager_) {
		imguiManager_->Finalize();
		delete imguiManager_;
		imguiManager_ = nullptr;
	}

	delete directInput_;
	directInput_ = nullptr;

	delete directXManager_;
	directXManager_ = nullptr;

	if (windowManager_) {
		windowManager_->Finalize();
		delete windowManager_;
		windowManager_ = nullptr;
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
