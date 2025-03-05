#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"



CMesh::CMesh()
	: CAsset(ASSET_TYPE::MESH)
	, VertexBufferDesc{}
	, VertexCount(0)
	, VretexSystemMemory(nullptr)
	, IndexBufferDesc{}
	, IndexCount(0)
	, IndexSystemMemory(nullptr)
{
}

CMesh::~CMesh()
{
	if (nullptr != VretexSystemMemory)
		delete[] VretexSystemMemory;
	if (nullptr != IndexSystemMemory)
		delete[] IndexSystemMemory;
}


int CMesh::Create(Vertex* _VtxSysMem, size_t _VtxCount, UINT* _IdxSysMem, size_t _IdxCount)
{
	VertexCount = (UINT)_VtxCount;
	IndexCount = (UINT)_IdxCount;

	// Create VertexBuffer
	VertexBufferDesc.ByteWidth = sizeof(Vertex) * (UINT)_VtxCount;
	VertexBufferDesc.MiscFlags = 0;

	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;  // 만들어질때 용도(vertex) 지정
	VertexBufferDesc.CPUAccessFlags = 0;
	VertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = _VtxSysMem;

	if (FAILED(_DEVICE->CreateBuffer(&VertexBufferDesc, &SubDesc, VertexBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	// Create IndexBuffer
	IndexBufferDesc.ByteWidth = sizeof(UINT) * (UINT)IndexCount;
	IndexBufferDesc.MiscFlags = 0;

	IndexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER; // 만들어질때 용도(index) 지정
	IndexBufferDesc.CPUAccessFlags = 0;
	IndexBufferDesc.Usage = D3D11_USAGE_DEFAULT;

	SubDesc = {};
	SubDesc.pSysMem = _IdxSysMem;

	if (FAILED(_DEVICE->CreateBuffer(&IndexBufferDesc, &SubDesc, IndexBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	// SystemMemory 유지
	VretexSystemMemory = new Vertex[_VtxCount];
	memcpy(VretexSystemMemory, _VtxSysMem, sizeof(Vertex) * _VtxCount);
	IndexSystemMemory = new UINT[_IdxCount];
	memcpy(IndexSystemMemory, _IdxSysMem, sizeof(UINT) * _IdxCount);

	return S_OK;
}

void CMesh::Binding()
{
	UINT Stride = sizeof(Vertex);
	UINT Offset = 0;
	_CONTEXT->IASetVertexBuffers(0, 1, VertexBuffer.GetAddressOf(), &Stride, &Offset);
	_CONTEXT->IASetIndexBuffer(IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::Render()
{
	Binding();
	_CONTEXT->DrawIndexed(IndexCount, 0, 0);
}
