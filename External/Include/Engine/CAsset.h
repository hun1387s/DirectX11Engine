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

    int         RefCount;           // 참조 카운트

public:
    const wstring& GetKey() { return Key; }
    const wstring& GetRelativePath() { return RelativePath; }
    ASSET_TYPE GetAssetType() { return Type; }

private:
    void AddRef() { RefCount++; }
    void Release() 
    {
        if (--RefCount <= 0)
            delete this;
    }
    
public:
    CAsset(ASSET_TYPE _type);
    CAsset(const CAsset& orig) = delete;    // 복사 방지
    ~CAsset();

    template<typename T> // 템플릿 클래스 프렌드 정의
    friend class Ptr;

    friend class CAssetMgr;

};

