#include "pch.h"
#include "CMeshRender.h"



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
	GetShader()->Binding();

	GetMesh()->Render();
}
