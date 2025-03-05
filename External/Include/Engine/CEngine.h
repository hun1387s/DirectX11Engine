#pragma once


class CEngine
	: public CSingleton<CEngine>
{
private:
	static CEngine* g_This;
	HWND	MainHwnd;
	POINT	Resolution;

public:
	HWND GetMainWnd() { return MainHwnd; }
	int init(HWND _hWnd, POINT _Resloution);

	void progress();


private:
	CEngine();
	CEngine(const CEngine& _origin) = delete;
public:
	~CEngine();
	friend class CSingleton<CEngine>;
};
