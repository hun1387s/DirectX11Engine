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
