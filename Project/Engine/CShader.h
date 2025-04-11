#pragma once
#include "CAsset.h"


class CShader :
    public CAsset
{
protected:
    ComPtr<ID3DBlob>			Err_Blob;

private:
    virtual int Load(const wstring& _FilePath) override { return S_OK; };
    virtual int Save(const wstring& _FilePath) override { return S_OK; };

public:
    virtual void Binding() = 0;

public:
    CShader(ASSET_TYPE type);
    ~CShader();
};

