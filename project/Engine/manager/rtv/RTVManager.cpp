#include "RTVManager.h"

#include <cassert>

#include "manager/dxgi/DXGIManager.h"
#include "directX/command/DirectXCommand.h"

void RTVManager::Initialize(DXGIManager* dxgi) {
	// DXGIのセット
	SetDXGI(dxgi);

}

void RTVManager::SetDXGI(DXGIManager* dxgi) {
	assert(dxgi);
	dxgi_ = dxgi;
}

