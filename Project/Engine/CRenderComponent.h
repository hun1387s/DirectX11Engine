#pragma once
#include "CComponent.h"

#include "assets.h"


class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh>          Mesh;
    Ptr<CGraphicShader> Shader;


public:
    virtual void render() = 0;

public:
    void SetMesh(Ptr<CMesh> mesh) { Mesh = mesh; }
    void SetShader(Ptr<CGraphicShader> shader) { Shader = shader; }

    Ptr<CMesh> GetMesh() { return Mesh; }
    Ptr<CGraphicShader> GetShader() { return Shader; }

public:
    CRenderComponent(COMPONENT_TYPE type);
    ~CRenderComponent();

};

