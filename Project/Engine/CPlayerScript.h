#pragma once
#include "CScript.h"


class CPlayerScript :
    public CScript
{
private:
    float       Speed;

public:
    virtual void tick() override;


public:
    CPlayerScript();
    ~CPlayerScript();
};

