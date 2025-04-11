#pragma once
#include "singleton.h"

#include "CPathMgr.h"
#include "assets.h"

// 자산(Asset) 관리를 담당하는 싱글톤 클래스
class CAssetMgr :
    public CSingleton<CAssetMgr>
{
    SINGLE(CAssetMgr) // 싱글톤 매크로 사용
private:
    // 자산을 저장하는 맵, ASSET_TYPE 개수만큼 배열로 구성
    map<wstring, Ptr<CAsset>> mapAsset[(UINT)ASSET_TYPE::END];


public:
    void init();
    void CreateDefaultMesh();
    void CreateDefaultTexture();
    void CreateDefaultMaterial();
    void CreateDefaultGraphicShader();
    void CreateDefaultComputShader();


public:
    template<typename T>
    Ptr<T> Load(const wstring& strKey, const wstring& _strRelativePath);

    // 특정 키 값을 기반으로 자산을 찾는 템플릿 함수
    template<typename T>
    Ptr<T> FindAsset(const wstring& key);

    // 특정 키와 자산을 추가하는 템플릿 함수
    template<typename T>
    void AddAsset(const wstring& _strKey, Ptr<T> _asset);
};


// 변수 템플릿을 사용하여 타입 비교를 위한 mybool 변수 정의
template<typename T1, typename T2>
constexpr bool mybool = false; // 기본적으로 false 설정

// 같은 타입인 경우 mybool 값을 true로 설정
template<typename T1>
constexpr bool mybool<T1, T1> = true;



// 템플릿을 활용한 자산 타입 반환 함수
template<typename T>
ASSET_TYPE GetAssetType()
{
    // 컴파일 타임에서 타입을 판별하여 상수 시간 내에 처리
    if constexpr (std::is_same_v<T, CMesh>)
        return ASSET_TYPE::MESH;

    if constexpr (mybool<T, CComputeShader>)
        return ASSET_TYPE::COMPUTE_SHADER;

    if constexpr (mybool<T, CGraphicShader>)
        return ASSET_TYPE::GRAPHICS_SHADER;

    if constexpr (mybool<T, CTexture>)
        return ASSET_TYPE::TEXTURE;

    // 기타 타입 판별 로직 주석 처리 (필요하면 확장 가능)
    // if (info.hash_code() == typeid(Prefab).hash_code())
    //     return ASSET_TYPE::PREFAB;
    // if (info.hash_code() == typeid(CTexture).hash_code())
    //     return ASSET_TYPE::TEXTURE;
    // if (info.hash_code() == typeid(CSound).hash_code())
    //     return ASSET_TYPE::SOUND;

}

template<typename T>
inline Ptr<T> CAssetMgr::Load(const wstring & strKey, const wstring & _strRelativePath)
{
    Ptr<CAsset> asset = FindAsset<T>(strKey).Get();
    if (nullptr != asset.Get())
    {
        return (T*)asset.Get();
    }

    wstring strFullPath = CPathMgr::GetInst()->GetContentPath();
    strFullPath += _strRelativePath;

    asset = new T;
    if (FAILED(asset->Load(strFullPath)))
    {
        MessageBox(nullptr, strFullPath.c_str(), L"에셋 로딩 실패", MB_OK);
        return nullptr;
    }


    return (T*)asset.Get();
}

// 특정 키 값을 통해 자산을 찾는 함수
template<typename T>
inline Ptr<T> CAssetMgr::FindAsset(const wstring& key)
{
    ASSET_TYPE type = GetAssetType<T>(); // 해당 타입의 자산 유형 가져오기

    // 자산을 저장한 맵에서 검색
    auto iter = mapAsset[(UINT)type].find(key);

    // 찾지 못한 경우 nullptr 반환
    if (iter == mapAsset[(UINT)type].end())
        return nullptr;

#ifdef _DEBUG
    // 디버그 모드에서는 dynamic_cast를 사용하여 안전한 형 변환 수행
    T* asset = dynamic_cast<T*>(iter->second.Get());
    return asset;
#else
    // 릴리즈 모드에서는 그냥 포인터 변환 수행
    return (T*)iter->second;
#endif
}

// 새로운 자산을 추가하는 함수
template<typename T>
inline void CAssetMgr::AddAsset(const wstring& _strKey, Ptr<T> _asset)
{
    // 이미 존재하는 자산인지 확인
    Ptr<T> findAsset = FindAsset<T>(_strKey);

    // 자산이 이미 존재하는 경우 assert 발생 (중복 방지)
    assert(findAsset.Get() == nullptr);

    ASSET_TYPE type = GetAssetType<T>(); // 해당 자산의 타입 확인

    // 맵에 자산 추가
    mapAsset[(UINT)type].insert(make_pair(_strKey, _asset.Get()));
    _asset->Key = _strKey; // 자산의 키 값을 설정
}

