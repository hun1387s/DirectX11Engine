#pragma once
#include "CEntity.h"

class CLayer;

class CLevel :
    public CEntity
{
private:
    CLayer*         arrLayer[MAX_LAYER];

public:
    CLevel();
    ~CLevel();

};

