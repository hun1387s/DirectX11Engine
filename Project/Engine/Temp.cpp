#include "pch.h"
#include "Temp.h"
#include "CDevice.h"

// Graphics Pipeline

//=====================
// IA (input assembler)
//=====================
// Vertext Buffer
// Index Buffer
// Topology
// Layout
// 
// ===================
// Vertex Shader Stage
// ===================
// 정점을 3차원 모델 좌표계에서 NDC 2차원 좌표로 맵핑
// 
// Tessellation
//	- Hull Shader
//	- Damain Shader
// 
// Geomatry Shader
// 
// ==========
// Rasterizer
// ==========
// 
// ============
// Pixel Shader
// ============
// 픽셀 당 호출되는 
// 각 픽셀의 색상을 지정해서 렌더타겟에 출력
// 
// ==================
// Output Merge State
// ==================
// DepthStencil State
// BlendState State
// 
// 최종 출력
// RenderTarget
// DepthStencilTexture
//


// 정점 정보를 저장하는 버퍼
ComPtr< ID3D11Buffer> VertexBuffer;

Vertex VtxArr[3] = {};

int TempInit()
{
	VtxArr[0].vPos = Vector3( 0.f,  1.f, 0.f);
	VtxArr[1].vPos = Vector3( 1.f, -1.f, 0.f);
	VtxArr[2].vPos = Vector3(-1.f, -1.f, 0.f);

	VtxArr[0].vColor = Vector4(1.f, 0.f, 0.f, 1.f);
	VtxArr[1].vColor = Vector4(0.f, 1.f, 0.f, 1.f);
	VtxArr[2].vColor = Vector4(0.f, 0.f, 1.f, 1.f);

	// 정점 버퍼 생성
	D3D11_BUFFER_DESC VertexBufferDesc = {};
	VertexBufferDesc.ByteWidth = sizeof(Vertex) * 3;
	VertexBufferDesc.MiscFlags = 0;

	VertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER; // 만들어질때 용도(vertex) 지정
	VertexBufferDesc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE; // 버퍼가 생성된 이후에 cpu에서 접근해 덮어쓰기가 가능하게 설정
	VertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = VtxArr;

	if (FAILED(DEVICE->CreateBuffer(&VertexBufferDesc, &SubDesc, VertexBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void TempReleas()
{
}

void TempTick()
{
}

void TempRender()
{
}
