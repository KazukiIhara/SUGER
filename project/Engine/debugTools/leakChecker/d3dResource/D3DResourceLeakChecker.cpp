// This
#include "debugTOols/leakChecker/d3dResource/D3DResourceLeakChecker.h"

// C++

// Microsoft
#include <wrl.h>

// DirectX
#include <dxgidebug.h>
#include <d3d12.h>
#include <dxgi1_6.h>

// MyHedder
#include "debugTools/logger/Logger.h"

D3DResourceLeakChecker* D3DResourceLeakChecker::GetInstance() {
	static D3DResourceLeakChecker instance;
	return &instance;
}

D3DResourceLeakChecker::~D3DResourceLeakChecker() {
	// リソースリークチェック
	Microsoft::WRL::ComPtr<IDXGIDebug1> debug;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&debug)))) {
		debug->ReportLiveObjects(DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_APP, DXGI_DEBUG_RLO_ALL);
		debug->ReportLiveObjects(DXGI_DEBUG_D3D12, DXGI_DEBUG_RLO_ALL);
		Logger::Log("Leak Check Complete\n");
	}
}
