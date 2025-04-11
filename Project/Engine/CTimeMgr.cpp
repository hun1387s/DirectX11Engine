#include "pch.h"
#include "CTimeMgr.h"

#include "CEngine.h"


CTimeMgr::CTimeMgr()
	: Frequency{}
	, CurCount{}
	, PrevCount{}
	, DeltaTime(0.f)
	, Time(0.f)
	, AccTime(0.f)
	, FrameCount(0)
{
}

CTimeMgr::~CTimeMgr()
{
}

void CTimeMgr::init()
{
	// 초당 카운트 수
	QueryPerformanceFrequency(&Frequency);
	QueryPerformanceCounter(&CurCount);
	PrevCount = CurCount;
}

void CTimeMgr::tick()
{
	QueryPerformanceCounter(&CurCount);
	
	DeltaTime = (float)(CurCount.QuadPart - PrevCount.QuadPart) / (float)Frequency.QuadPart;

	PrevCount = CurCount;

	// 프로그램 누적 시간
	Time += DeltaTime;

	AccTime += DeltaTime;
	++FrameCount;
	if (1.f < AccTime)
	{
		HWND MainWnd = CEngine::GetInst()->GetMainWnd();
		wchar_t _text[255] = {};
		swprintf_s(_text, L"FPS : %d, DeltaTime : %f", FrameCount, DeltaTime);
		SetWindowText(MainWnd, _text);

		AccTime -= 1.f;
		FrameCount = 0;
	}
}
