#include "pch.h"
#include "CEngine.h"

#include "CDevice.h"
#include "CTimeMgr.h"
#include "CPathMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"

#include "Temp.h"

CEngine* CEngine::g_This = nullptr;



CEngine::CEngine()
	: MainHwnd(nullptr)
	, Resolution{}
{
}

CEngine::~CEngine()
{
	TempReleas();
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

	// Manager Init
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CAssetMgr::GetInst()->init();

	if (FAILED(TempInit()))
	{
		MessageBox(nullptr, L"TempInit 초기화 실패", L"VertexBuffer 생성 실패", MB_OK);
		return E_FAIL;
	}

	return S_OK;
}

void CEngine::progress()
{
	// ============
	// Manager tick
	// ============
	CTimeMgr::GetInst()->tick();
	CKeyMgr::GetInst()->tick();
	
	// Object tick
	TempTick();


	// =========
	// Rengering
	// =========
	// Target Clear
	float ClearColor[4] = { 0.4f, 0.7f, 0.7f, 1.f };
	CDevice::GetInst()->ClearTarget(ClearColor);

	

	// Object Render
	TempRender();
	
	// SwapChain->Present();
	CDevice::GetInst()->Present();
}



