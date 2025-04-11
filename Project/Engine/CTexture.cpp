#include "pch.h"
#include "CTexture.h"
#include "CDevice.h"

CTexture::CTexture()
    : CAsset(ASSET_TYPE::TEXTURE)
{}

CTexture::~CTexture()
{}


void CTexture::Binding(int _registerNum)
{
    _CONTEXT->PSSetShaderResources(_registerNum, 1, ShaderResourceView.GetAddressOf());
}

int CTexture::Load(const wstring & _FilePath)
{
    wchar_t Ext[50] = {};

    _wsplitpath_s(_FilePath.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, Ext, 50);

    wstring strExt = Ext;

    HRESULT hr = E_FAIL;
    if (strExt == L".dds" || strExt == L".DDS")
    {
        // .dds .DDS
        hr = LoadFromDDSFile(_FilePath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, Image);
    }
    else if (strExt == L".tga" || strExt == L".TGA")
    {
        // .tga .TGA
        hr = LoadFromTGAFile(_FilePath.c_str(), nullptr, Image);
    }
    else
    {
        // .png .jpg .jpeg .bmp
        hr = LoadFromWICFile(_FilePath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, Image);
    }

    if (FAILED(hr))
    {
        MessageBox(nullptr, L"텍스쳐 로딩 실패", L"텍스쳐 로딩 실패", MB_OK);
        return E_FAIL;
    }


    // Texture2D Dscription 작성해서 Texture2D 객체 생성
    // Texture2D 객체를 이용해서 ShaderResourceView 생성
    hr = CreateShaderResourceView(_DEVICE
                                , Image.GetImages()
                                , Image.GetImageCount()
                                , Image.GetMetadata()
                                , ShaderResourceView.GetAddressOf() );
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"ShaderResourceView 생성 실패", L"텍스쳐 로딩 실패", MB_OK);
        return E_FAIL;
    }


    ShaderResourceView->GetResource((ID3D11Resource**)Tex2D.GetAddressOf());

    return hr;
}

int CTexture::Save(const wstring & _FilePath)
{
    return 0;
}

