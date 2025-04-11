#pragma once
#include "CAsset.h"

class CTexture :
    public CAsset
{
private:
    ScratchImage                        Image;
    ComPtr<ID3D11Texture2D>             Tex2D;
    ComPtr<ID3D11ShaderResourceView>    ShaderResourceView;

public:
    void Binding(int _registerNum);

private:
    virtual int Load(const wstring& _FilePath);
    virtual int Save(const wstring& _FilePath);

public:
    CTexture();
    ~CTexture();
};

