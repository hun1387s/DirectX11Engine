#include "pch.h"
#include "CLevel.h"

#include "CLayer.h"



CLevel::CLevel()
	: arrLayer{}
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		arrLayer[i] = new CLayer;
	}
}

CLevel::~CLevel()
{
	Safe_Del_Array(arrLayer);
}


void CLevel::AddObject(UINT _layerIdx, CGameObject* _obj)
{
	arrLayer[_layerIdx]->AddObject(_obj);
}

void CLevel::begin()
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		arrLayer[i]->begin();
	}
}

void CLevel::tick()
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		arrLayer[i]->tick();
	}
}

void CLevel::finaltick()
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		arrLayer[i]->finaltick();
	}
}

void CLevel::render()
{
	for (UINT i = 0; i < MAX_LAYER; i++)
	{
		arrLayer[i]->render();
	}
}
