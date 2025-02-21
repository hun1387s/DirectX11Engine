#pragma once
#include "CShader.h"

class CGraphicShader :
    public CShader
{
private:
    ComPtr<ID3DBlob>            VS_Blob;
    ComPtr<ID3DBlob>            PS_Blob;

    ComPtr<ID3D11VertexShader>  VS;
    ComPtr<ID3D11PixelShader>   PS;

    ComPtr<ID3D11InputLayout>   Layout;

    D3D11_PRIMITIVE_TOPOLOGY    Topology;

public:
    int CreateVertexShader(const wstring& filePath, const string& VSfuncName);
    int CreatePixelShader(const wstring& filePath, const string& PSfuncName);

    void SetTopology(D3D11_PRIMITIVE_TOPOLOGY topology) { Topology = topology; }

    virtual void Binding() override;

public:
    CGraphicShader();
    ~CGraphicShader();
};

