#pragma once
#include "CEntity.h"


class CAsset :
    public CEntity
{
private:
    wstring     Key;                // 로딩된 키값
    wstring     RelativePath;       // 상대 경로

    // RTTI (Run-Time Type Information)에 활용 가능
    const ASSET_TYPE  Type;         // 에셋 타입

public:
    const wstring& GetKey() { return Key; }
    const wstring& GetRelativePath() { return RelativePath; }
    ASSET_TYPE GetAssetType() { return Type; }

public:
    CAsset(ASSET_TYPE _type);
    ~CAsset();

};

