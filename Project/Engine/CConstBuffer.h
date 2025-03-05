#pragma once
#include "CEntity.h"


class CConstBuffer : public CEntity
{
private:
	// 상수버퍼(ConstantBuffer): 물체의 위치, 크기, 회전 (transform)
	ComPtr<ID3D11Buffer>	ConstantBuffer;
	D3D11_BUFFER_DESC		Buffer_Desc;

	CB_TYPE					Type;

public:
	int Create(size_t bufferSize, CB_TYPE type);

	void SetData(void* data);
	void Binding();

public:
	CConstBuffer();
	~CConstBuffer();
};

