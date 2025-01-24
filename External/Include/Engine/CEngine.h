#pragma once


// Singleton패턴으로 생성
// 데이터영역 싱글톤
class CEngine
{
private:
	static CEngine* g_This;
	HWND	MainHwnd;
	POINT	Resolution;

public:
	int init(HWND _hWnd, POINT _Resloution);

	void progress();

public:
	static CEngine* GetInst()
	{
		static CEngine mgr;
		return &mgr;
	}

private:
	CEngine();
	CEngine(const CEngine& _origin) = delete;
	~CEngine();
};
