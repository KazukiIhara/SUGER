#include "RenderTexture.h"

#include <cassert>

#include "directX/dxgi/DXGIManager.h"
#include "directX/command/DirectXCommand.h"
#include "manager/rtv/RTVManager.h"
#include "manager/srvUav/SRVUAVManager.h"

void RenderTexture::Initialize(DXGIManager* dxgi, DirectXCommand* command, RTVManager* rtvManager, SRVUAVManager* srvUavManager) {
	// インスタンスをセット
	SetDXGI(dxgi);
	SetCommand(command);
	SetRTVManager(rtvManager);
	SetSRVUAVManager(srvUavManager);
}

void RenderTexture::SetDXGI(DXGIManager* dxgi) {
	assert(dxgi);
	dxgi_ = dxgi;
}

void RenderTexture::SetCommand(DirectXCommand* command) {
	assert(command);
	command_ = command;
}

void RenderTexture::SetRTVManager(RTVManager* rtvManager) {
	assert(rtvManager);
	rtvManager_ = rtvManager;
}

void RenderTexture::SetSRVUAVManager(SRVUAVManager* srvUavManager) {
	assert(srvUavManager);
	srvUavManager_ = srvUavManager;
}
