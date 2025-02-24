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

#include "CGameObject.h"
#include "CTransform.h"
#include "CMeshRender.h"

CGameObject* object = nullptr;


int TempInit()
{
	assert(false);
	object = new CGameObject;
	object->AddComponent(new CTransform);
	object->AddComponent(new CMeshRender);

	object->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	object->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	return S_OK;
}

void TempReleas()
{
	delete object;
}

void TempTick()
{
	float DT = CTimeMgr::GetInst()->GetDeltaTime();

	object->tick();
	object->finaltick();

}

void TempRender()
{
	object->render();	
}
