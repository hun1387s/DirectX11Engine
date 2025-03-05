#include "pch.h"
#include "CKeyMgr.h"


// 내가 만든 KEY 값과 같은 순서로 만든 배열
UINT arrVK[(int)KEY::KEY_END] =
{
	VK_LEFT,	//LEFT,
	VK_RIGHT,	//RIGHT,
	VK_UP,		//UP,
	VK_DOWN,	//DOWN,
	'Q',		//Q,
	'W',		//W,
	'E',		//E,
	'R',		//R,
	'T',		//T,
	'Y',		//Y,
	'U',		//U,
	'I',		//I,
	'O',		//O,
	'P',		//P,
	'A',		//A,
	'S',		//S,
	'D',		//D,
	'F',		//F,
	'G',		//G,
	'H',		//H,
	'J',		//J,
	'K',		//K,
	'L',		//L,
	'Z',		//Z,
	'X',		//X,
	'C',		//C,
	'V',		//V,
	'B',		//B,
	'N',		//N,
	'M',		//M,

	VK_CONTROL,	//CTRL, 
	VK_MENU,    //ALT, 
	VK_SHIFT,   //LSHIFT, 
	VK_SPACE,   //SPACE, 
	VK_RETURN,  //ENTER, 
	VK_ESCAPE,  //ESCAPE,

	//LAST,
};


CKeyMgr::CKeyMgr()
{
}


CKeyMgr::~CKeyMgr()
{
}

void CKeyMgr::init()
{
	for (UINT i = 0; i < (UINT)KEY::KEY_END; i++)
	{
		KeyInfo info = {};
		info.State = KEY_STATE::NONE;
		info.PrevPressed = false;

		vecKey.push_back(info);
	}
}

void CKeyMgr::tick()
{
	for (size_t i = 0; i < vecKey.size(); i++)
	{
		// 키가 눌러졌다.
		if (GetAsyncKeyState(arrVK[i]) & 0x8001)
		{
			if (vecKey[i].PrevPressed)
			{
				// 이전에도 눌려있었다.
				vecKey[i].State = KEY_STATE::PRESSED;
			}
			else
			{
				// 이전에는 눌려있지 않았다.
				vecKey[i].State = KEY_STATE::TAP;
			}
			vecKey[i].PrevPressed = true;
		}
		// 키가 안눌러졌다.
		else
		{
			if (vecKey[i].PrevPressed)
			{
				// 이전에는 눌려있었다.
				vecKey[i].State = KEY_STATE::RELEASED;
			}
			else
			{
				// 이전에도 눌려있지 않았다.
				vecKey[i].State = KEY_STATE::NONE;
			}
			vecKey[i].PrevPressed = false;
		}
	}
}
