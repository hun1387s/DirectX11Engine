#pragma once
#include "CAsset.h"


class CMesh :
    public CAsset
{
private:
    ComPtr<ID3D11Buffer>    VertexBuffer;
    D3D11_BUFFER_DESC       VertexBufferDesc;
    UINT                    VertexCount;
    Vertex*                   VretexSystemMemory;

    ComPtr<ID3D11Buffer>    IndexBuffer;
    D3D11_BUFFER_DESC       IndexBufferDesc;
    UINT                    IndexCount;
    UINT*                   IndexSystemMemory;

private:
    void Binding();

public:
    int Create(Vertex* _VtxSysMem, size_t VtxCount, UINT* _IdxSysMem, size_t IdxCount);


    void Render();
    
public:
    CMesh();
    ~CMesh();
};

