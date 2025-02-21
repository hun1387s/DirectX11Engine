#include "pch.h"
#include "CAsset.h"

CAsset::CAsset(ASSET_TYPE _type)
	: Type(_type)
	, RefCount(0)
{
}

CAsset::~CAsset()
{
}
