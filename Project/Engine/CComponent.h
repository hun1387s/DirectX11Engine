#pragma once
#include "CEntity.h"
#include "CGameObject.h"

class CComponent :
    public CEntity
{
private:
    CGameObject*            owner;  // 해당 컴포넌트를 소유한 오브젝트 주소
    const COMPONENT_TYPE    type;   // 본인이 무슨 컴포넌트인지

public:
    virtual void begin() {}
    virtual void tick() {}
    virtual void finaltick() = 0;

public:
    COMPONENT_TYPE GetComponentType() { return type; }
    CGameObject* GetOwner() { return owner; }

public:
    CComponent(COMPONENT_TYPE _type);
    ~CComponent();

    friend class CGameObject;
};

