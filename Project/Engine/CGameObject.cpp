#include "pch.h"
#include "CGameObject.h"

#include "CComponent.h"
#include "CRenderComponent.h"
#include "CScript.h"

CGameObject::CGameObject()
	: arrComponent{}
	, renderComponent(nullptr)
{
}

CGameObject::~CGameObject()
{
	Safe_Del_Array(arrComponent);
}

void CGameObject::begin()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (nullptr != arrComponent[i])
			arrComponent[i]->begin();
	}

	for (size_t i = 0; i < vecScript.size(); i++)
	{
		vecScript[i]->begin();
	}
}

void CGameObject::tick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (nullptr != arrComponent[i])
			arrComponent[i]->tick();
	}

	for (size_t i = 0; i < vecScript.size(); i++)
	{
		vecScript[i]->tick();
	}
}

void CGameObject::finaltick()
{
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; i++)
	{
		if (nullptr != arrComponent[i])
			arrComponent[i]->finaltick();
	}
}

void CGameObject::render()
{
	if (renderComponent)
		renderComponent->render();
}

void CGameObject::AddComponent(CComponent* component)
{
	// 입력으로 들어오는 컴포넌트의 타입 확인
	COMPONENT_TYPE type = component->GetComponentType();

	// 입력된 컴포넌트가 Script 종류인 경우
	if (COMPONENT_TYPE::SCRIPT == type)
	{
		vecScript.push_back((CScript*)component);
	}
	else
	{
		// 중복 입력된 컴포넌트라면
		assert(!arrComponent[(UINT)type]);

		// 입력된 컴포넌트가 렌더 컴포넌트인지
		CRenderComponent* cast_renderComponent = dynamic_cast<CRenderComponent*>(component);

		if (nullptr != cast_renderComponent)
		{
			// 중복 입력된 렌더 컴포넌트라면
			assert(!renderComponent);

			renderComponent = cast_renderComponent;
		}

		// 입력된 컴포넌트를 배열의 알맞은 인덱스 자리에 주소값을 기록
		arrComponent[(UINT)type] = component;
	}

	// 컴포넌트의 소유 오브젝트를 본인임을 알림
	component->owner = this;
}



