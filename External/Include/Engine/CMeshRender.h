#pragma once
#include "CRenderComponent.h"


class CMeshRender :
    public CRenderComponent
{

public:
    virtual void finaltick() override;
    virtual void render() override;

public:
    CMeshRender();
    ~CMeshRender();
};

