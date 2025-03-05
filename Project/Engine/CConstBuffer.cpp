#include "pch.h"
#include "CConstBuffer.h"
#include "CDevice.h"

CConstBuffer::CConstBuffer()
	: Buffer_Desc{}
	, Type(CB_TYPE::END)
{

}

CConstBuffer::~CConstBuffer()
{

}

int CConstBuffer::Create(size_t bufferSize, CB_TYPE type)
{
	Type = type;

	Buffer_Desc.ByteWidth = bufferSize;
	Buffer_Desc.MiscFlags = 0;

	// 버퍼 용도 설정
	Buffer_Desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	// 생성 이후 읽기 쓰기 가능
	Buffer_Desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	Buffer_Desc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(_DEVICE->CreateBuffer(&Buffer_Desc, nullptr, ConstantBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}
	return 0;
}

void CConstBuffer::SetData(void* data)
{
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	_CONTEXT->Map(ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);

	memcpy(tSub.pData, data, Buffer_Desc.ByteWidth);
	_CONTEXT->Unmap(ConstantBuffer.Get(), 0);
}

void CConstBuffer::Binding()
{
	_CONTEXT->VSSetConstantBuffers((UINT)Type, 1, ConstantBuffer.GetAddressOf());
}

