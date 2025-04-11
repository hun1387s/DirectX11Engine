#pragma once
#include "CComponent.h"

#include "assets.h"


class CRenderComponent :
    public CComponent
{
private:
    Ptr<CMesh>          Mesh;
    Ptr<CGraphicShader> Shader;

    Ptr<CTexture>       Texture;

public:
    virtual void render() = 0;

public:
    void SetMesh(Ptr<CMesh> mesh) { Mesh = mesh; }
    void SetShader(Ptr<CGraphicShader> shader) { Shader = shader; }
    void SetTexture(Ptr<CTexture> texture) { Texture = texture; }

    Ptr<CMesh> GetMesh() { return Mesh; }
    Ptr<CGraphicShader> GetShader() { return Shader; }
    Ptr<CTexture> GetTexture() { return Texture; }

public:
    CRenderComponent(COMPONENT_TYPE type);
    ~CRenderComponent();

};

