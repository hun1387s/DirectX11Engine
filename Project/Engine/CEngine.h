#pragma once


// Singleton패턴으로 생성
// 데이터영역 싱글톤
class CEngine
	: public CSingleton<CEngine>
{
private:
	static CEngine* g_This;
	HWND	MainHwnd;
	POINT	Resolution;

public:
	int init(HWND _hWnd, POINT _Resloution);

	void progress();


private:
	CEngine();
	CEngine(const CEngine& _origin) = delete;
public:
	~CEngine();
	friend class CSingleton<CEngine>;
};
