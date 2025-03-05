#pragma once
#include "CLevel.h"

class CGameObject;

class CLayer :
    public CLevel
{

private:
    vector<CGameObject*>        vecObject;


public:
    CLayer();
    ~CLayer();
};

