#pragma once


// Singleton패턴으로 생성
class CEngine
{
private:
	static CEngine* g_This;

	//HWND	m_hMainWnd;

public:
	//정적 맴버함수 : 객체가 없어도 호출가능
	static CEngine* GetInst()
	{
		if (nullptr == g_This)
		{
			g_This = new CEngine;
		}
		
		return g_This;
	}

	static void Destroy()
	{
		if (nullptr == g_This)
		{
			delete g_This;
			g_This = nullptr;
		}
	}

private:
	CEngine();
};

