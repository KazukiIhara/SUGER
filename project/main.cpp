#include <Windows.h>
#include <memory>

#include "debugTools/logger/Logger.h"
#ifdef _DEBUG
#include "debugTools/leakChecker/d3dResource/D3DResourceLeakChecker.h"
#endif // _DEBUG
#include "myGame/MyGame.h"

// Lib
#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dxcompiler.lib")

#pragma comment(lib,"winmm.lib")

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	Logger::Log("Hello,DirectX!\n");

#ifdef _DEBUG
	// リークチェッカのインスタンスを最初に取得
	D3DResourceLeakChecker* leakCheck = D3DResourceLeakChecker::GetInstance();
#endif // _DEBUG

	std::unique_ptr<SUGER> game = std::make_unique<MyGame>();
	game->Run();

	Logger::Log("Bye,DirectX...\n");

	return 0;
}