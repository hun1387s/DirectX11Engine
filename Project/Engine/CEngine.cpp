#include "pch.h"
#include "CEngine.h"


CEngine* CEngine::g_This = nullptr;



CEngine::CEngine()
	: m_hMainHwnd(nullptr)
	, m_Resolution{}
{
}

int CEngine::init(HWND _hWnd, POINT _Resloution)
{
	m_hMainHwnd = _hWnd;
	m_Resolution = _Resloution;

	// 윈도우 크기 설정
	RECT rt = { 0, 0, m_Resolution.x, m_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(m_hMainHwnd, nullptr, 0, 0, rt.right - rt.left, rt.top - rt.bottom, 0);

	// DirectX11

	return S_OK;
}


CEngine::~CEngine()
{
}
