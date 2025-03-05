#include "pch.h"
#include "CPlayerScript.h"


CPlayerScript::CPlayerScript()
	: Speed(1.f)
{
}

CPlayerScript::~CPlayerScript()
{
}

void CPlayerScript::tick()
{
	// 키 입력에 따른 위치이동
	Vector3 pos = GetOwner()->Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
		pos.y += DT * Speed;
	if (KEY_PRESSED(KEY::S))
		pos.y -= DT * Speed;
	if (KEY_PRESSED(KEY::A))
		pos.x -= DT * Speed;
	if (KEY_PRESSED(KEY::D))
		pos.x += DT * Speed;

	GetOwner()->Transform()->SetRelativePos(pos);
}
