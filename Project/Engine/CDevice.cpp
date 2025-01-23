#include "pch.h"
#include "CDevice.h"


CDevice::CDevice()
	: MainWnd(nullptr)
	, RenderResolution{}
	, Device(nullptr)
	, Context(nullptr)
	, SwapChain(nullptr)
	, RenderTargetTex(nullptr)
	, RenderTargetView(nullptr)
	, DepthStencilTex(nullptr)
	, DepthStencilView(nullptr)
{
}

CDevice::~CDevice()
{
	Device->Release();
	Context->Release();
}


int CDevice::init(HWND _hwnd, POINT _Resolution)
{
	MainWnd = _hwnd;
	RenderResolution = _Resolution;

	UINT flag = 0;
#ifdef _DEBUG
	flag = D3D11_CREATE_DEVICE_DEBUG;
#endif
	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;

	D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE,
		nullptr, flag, nullptr, 0, D3D11_SDK_VERSION,
		&Device, &level, &Context);

	return S_OK;
}
