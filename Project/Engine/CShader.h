#pragma once
#include "CAsset.h"


class CShader :
    public CAsset
{
protected:
    ComPtr<ID3DBlob>			Err_Blob;
    
public:
    virtual void Binding() = 0;

public:
    CShader(ASSET_TYPE type);
    ~CShader();
};

