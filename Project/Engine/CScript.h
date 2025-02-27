#pragma once
#include "CComponent.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CAssetMgr.h"

#include "CTransform.h"

class CScript :
    public CComponent
{
private:


public:
    virtual void tick() = 0;
    virtual void finaltick() final {} // 이후 사용안할 가상함수 오버라이드 방지

public:
    CScript();
    ~CScript();
};

