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
#include "CPlayerScript.h"

CGameObject* object1 = nullptr;
CGameObject* object2 = nullptr;


int TempInit()
{
	object1 = new CGameObject;
	object1->AddComponent(new CTransform);
	object1->AddComponent(new CMeshRender);
	object1->AddComponent(new CPlayerScript);

	object1->Transform()->SetRelativeScale(0.2f, 0.2f, 0.2f);

	object1->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	object1->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	object2 = new CGameObject;
	object2->AddComponent(new CTransform);
	object2->AddComponent(new CMeshRender);
	//object2->AddComponent(new CPlayerScript);
		  
	object2->Transform()->SetRelativeScale(0.4f, 0.4f, 0.4f);
		  
	object2->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	object2->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	return S_OK;
}

void TempReleas()
{
	delete object1;
	delete object2;
}

void TempTick()
{
	object1->tick();
	object2->tick();

	object1->finaltick();
	object2->finaltick();
}

void TempRender()
{
	object1->render();	
	object2->render();
}
