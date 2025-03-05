#pragma once
#include "CEntity.h"

class CLayer;
class CGameObject;

class CLevel :
    public CEntity
{
private:
    CLayer*         arrLayer[MAX_LAYER];

public:
    void AddObject(UINT _layerIdx, CGameObject* _obj);
    void begin();
    void tick();
    void finaltick();
    void render();


public:
    CLevel();
    ~CLevel();

};

