#include "pch.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CGameObject.h"

#include "CTransform.h"
#include "CMeshRender.h"
#include "CPlayerScript.h"

CLevelMgr::CLevelMgr()
	: curLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != curLevel)
	{
		delete curLevel;
		curLevel = nullptr;
	}
}

void CLevelMgr::init()
{
	curLevel = new CLevel;

	CGameObject* object = new CGameObject;
	object->AddComponent(new CTransform);
	object->AddComponent(new CMeshRender);
	object->AddComponent(new CPlayerScript);

	object->Transform()->SetRelativeScale(0.66f, 1.f, 0.2f);

	//object->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"CircleMesh"));
    object->MeshRender()->SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	object->MeshRender()->SetShader(CAssetMgr::GetInst()->FindAsset<CGraphicShader>(L"Std2DShader"));

	curLevel->AddObject(0, object);
}

void CLevelMgr::tick()
{
	if (nullptr != curLevel)
	{
		curLevel->tick();
		curLevel->finaltick();
	}
}

void CLevelMgr::render()
{
	if (nullptr != curLevel)
		curLevel->render();
}
