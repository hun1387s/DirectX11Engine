#include "pch.h"
#include "CEntity.h"


UINT CEntity::NextID = 0;

CEntity::CEntity()
	: ID(NextID++)
{
}

// ID 곂침 방지로 복사생성자 지정
CEntity::CEntity(const CEntity& _origin)
	: ID(NextID++)
{
}

CEntity::~CEntity()
{
}
