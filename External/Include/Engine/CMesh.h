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

    virtual int Load(const wstring& _FilePath) override { return S_OK; };
    virtual int Save(const wstring& _FilePath) override { return S_OK; };
    
public:
    CMesh();
    ~CMesh();
};

