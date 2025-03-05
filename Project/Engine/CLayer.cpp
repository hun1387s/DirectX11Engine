#include "pch.h"
#include "CLayer.h"
#include "CGameObject.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
	Safe_Del_Vector(vecObject);
}

void CLayer::begin()
{
	for (size_t i = 0; i < vecObject.size(); i++)
	{
		vecObject[i]->begin();
	}
}

void CLayer::tick()
{
	for (size_t i = 0; i < vecObject.size(); i++)
	{
		vecObject[i]->tick();
	}
}

void CLayer::finaltick()
{
	for (size_t i = 0; i < vecObject.size(); i++)
	{
		vecObject[i]->finaltick();
	}
}

void CLayer::render()
{
	for (size_t i = 0; i < vecObject.size(); i++)
	{
		vecObject[i]->render();
	}
}


