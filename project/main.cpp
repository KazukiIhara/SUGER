#include <Windows.h>
#include <memory>

#include "Logger.h"
#include "WindowManager.h"
#include "DirectXManager.h"
#include "DirectInput.h"
#include "SRVManager.h"
#include "TextureManager.h"
#include "ImGuiManager.h"

// Lib
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

#pragma comment(lib,"winmm.lib")

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Logger::Log("Hello,DirectX!\n");

	std::unique_ptr<WindowManager> windowManager;
	windowManager = std::make_unique<WindowManager>();
	windowManager->Initialize();

	std::unique_ptr<DirectInput> directInput;
	directInput = std::make_unique<DirectInput>();
	directInput->Initialize(windowManager.get());

	std::unique_ptr<DirectXManager> directXManager;
	directXManager = std::make_unique<DirectXManager>();
	directXManager->Initialize(windowManager.get());

	std::unique_ptr<SRVManager> srvManager;
	srvManager = std::make_unique<SRVManager>();
	srvManager->Initialize(directXManager.get());

	std::unique_ptr<ImGuiManager> imguiManager;
	imguiManager = std::make_unique<ImGuiManager>();
	imguiManager->Initialize(windowManager.get(), directXManager.get(), srvManager.get());

	std::unique_ptr<TextureManager> textureManager;
	textureManager = std::make_unique<TextureManager>();
	textureManager->Initialize(directXManager.get(), srvManager.get());

	textureManager->Load("resources/images/uvChecker.png");


	while (true) {
		if (windowManager->ProcessMessage()) {
			break;
		}

		directInput->Update();
		
		imguiManager->BeginFrame();

		ImGui::ShowDemoWindow();


		imguiManager->EndFrame();
		directXManager->PreDraw();
		srvManager->PreDraw();


		imguiManager->Draw();
		directXManager->PostDraw();

		if (directInput->PushKey(DIK_ESCAPE)) {
			break;
		}
	}


	imguiManager->Finalize();
	windowManager->Finalize();

	return 0;
}