#include <Windows.h>

#include "Logger.h"
#include "WindowManager.h"
#include "DirectXManager.h"
#include "DirectInput.h"
#include "imgui.h"

#include <memory>

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

	while (true) {

		directInput->Update();

		if (windowManager->ProcessMessage()) {
			break;
		}

		directXManager->PreDraw();

		directXManager->PostDraw();

		if (directInput->PushKey(DIK_ESCAPE)) {
			break;
		}
	}

	windowManager->Finalize();

	return 0;
}