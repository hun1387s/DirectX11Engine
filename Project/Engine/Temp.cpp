#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"
#include "CAssetMgr.h"

#include "CMesh.h"
#include "CConstBuffer.h"
#include "CGraphicShader.h"


// 물체의 위치, 크기, 회전
Transform transform = {};


int TempInit()
{
	
	return S_OK;
}

void TempReleas()
{

}

void TempTick()
{
	float DT = CTimeMgr::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		transform.Position.y += 1.f * DT;
	}
	if (KEY_PRESSED(KEY::S))
	{
		transform.Position.y -= 1.f * DT;
	}
	if (KEY_PRESSED(KEY::A))
	{
		transform.Position.x -= 1.f * DT;
	}
	if (KEY_PRESSED(KEY::D))
	{
		transform.Position.x += 1.f * DT;
	}

	// SysMem -> GPU
	CConstBuffer* constBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRNSFORM);
	constBuffer->SetData(&transform);
	constBuffer->Binding();
}

void TempRender()
{
	auto shader = CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader");
	shader->Binding();

	Ptr<CMesh> mesh = CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh");
	mesh->Render();
	
}
