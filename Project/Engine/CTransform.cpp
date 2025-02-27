#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"


CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, relativeScale(Vector3(1.f, 1.f, 1.f))

{
}

CTransform::~CTransform()
{
}

void CTransform::finaltick()
{

}

void CTransform::Binding()
{
	// SysMem -> GPU
	CConstBuffer* constBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRNSFORM);
	Transform trans = {};
	trans.Position = relativePos;
	trans.Scale = relativeScale;

	constBuffer->SetData(&trans);
	constBuffer->Binding();
}
