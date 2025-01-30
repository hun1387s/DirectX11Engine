#pragma once
#include "singleton.h"

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q, W, E, R, T, Y, U, I, O, P,
	A, S, D, F, G, H, J, K, L,
	Z, X, C, V, B, N, M,
	CTRL, ALT, LSHIFT, SPACE, ENTER, ESCAPE,


	KEY_END,

};

enum class KEY_STATE
{
	
	TAP,		// 막 누른 시점
	PRESSED,	// 누르고 있는
	RELEASED,	// 막 땐 시점
	NONE,		// 눌리지 않음
};

struct KeyInfo
{
	KEY_STATE	State;			// 키의 상태값
	bool		PrevPressed;	// 이전 프레임에서의 눌린 여부
};


class CKeyMgr :
    public CSingleton<CKeyMgr>
{
    SINGLE(CKeyMgr);
private:
	vector<KeyInfo>		vecKey;


public:
	void init();
	void tick();

	KEY_STATE GetKeyState(KEY _key) { return vecKey[(UINT)_key].State; }
};

