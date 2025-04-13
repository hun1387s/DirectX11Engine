#include "pch.h"
#include "CMeshRender.h"

#include "CTransform.h"

CMeshRender::CMeshRender()
	: CRenderComponent(COMPONENT_TYPE::MESHRENDER)
{
}

CMeshRender::~CMeshRender()
{
}


void CMeshRender::finaltick()
{
}

void CMeshRender::render()
{
	// 오브젝트의 위치값을 상수버퍼를 통해 바인딩
	if (nullptr != GetOwner())
		GetOwner()->Transform()->Binding();

	// 사용할 쉐이더 바인딩
	if (nullptr != GetShader().Get())
		GetShader()->Binding();

    // 사용할 텍스쳐 바인딩
	if (nullptr != GetTexture().Get())
		GetTexture()->Binding(0);

	// 메시 바인딩 및 렌더링
	if (nullptr != GetTexture().Get())
		GetMesh()->Render();
}
