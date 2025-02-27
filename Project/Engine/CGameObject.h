#pragma once
#include "CEntity.h"

class CComponent;
class CRenderComponent;
class CTransform;
class CMeshRender;
class CScript;

class CGameObject :
    public CEntity
{
private:
    CComponent*         arrComponent[(UINT)COMPONENT_TYPE::END];
    CRenderComponent*   renderComponent;

    vector<CScript*>     vecScript;


public:
    void begin();       // 레벨이 시작될 때, 레벨에 합류할 때
    void tick();        // 매 프레임마다 호출,  DT 동안 할 일을 구현
    void finaltick();   // tick 에서 발생한 일들의 마무리 작업 or 리소스 바인딩 및 관련 데이터 연산
    void render();      // 화면에 그려지는 함수

public:
    void AddComponent(CComponent* component);
    CComponent* GetComponent(COMPONENT_TYPE type) { return arrComponent[(UINT)type]; }

    CTransform* Transform() { return (CTransform*)arrComponent[(UINT)COMPONENT_TYPE::TRANSFORM]; }
    CMeshRender* MeshRender() { return (CMeshRender*)arrComponent[(UINT)COMPONENT_TYPE::MESHRENDER]; }


public:
    CGameObject();
    ~CGameObject();
};

