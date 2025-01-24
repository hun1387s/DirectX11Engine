#include "pch.h"
#include "CEngine.h"
#include "CDevice.h"


CEngine* CEngine::g_This = nullptr;



CEngine::CEngine()
	: MainHwnd(nullptr)
	, Resolution{}
{
}

int CEngine::init(HWND _hWnd, POINT _Resloution)
{
	MainHwnd = _hWnd;
	Resolution = _Resloution;

	// 윈도우 크기 설정
	RECT rt = { 0, 0, Resolution.x, Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(MainHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);

	// DirectX11
	if (FAILED(CDevice::GetInst()->init(MainHwnd, Resolution)))
	{
		MessageBox(MainHwnd, L"Device 초기화 실패", L"Device 초기화 실패", MB_OK);
		return E_FAIL;
	}

	// SwapChain 생성



	return S_OK;
}


CEngine::~CEngine()
{
}
