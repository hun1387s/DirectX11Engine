#pragma once
#include "CEntity.h"

class CGameObject;

class CLayer : public CEntity
{

private:
    vector<CGameObject*>        vecObject;

public:
    void AddObject(CGameObject* _obj) { vecObject.push_back(_obj); }
    void begin();
    void tick();
    void finaltick();
    void render();

public:
    CLayer();
    ~CLayer();
};

