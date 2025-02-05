#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CMesh.h"

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
// 정점을 Local Space에서 World, View, Clip Space를 거쳐 
// NDC(Normalized Device Coordinates)로 변환
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
// 각 픽셀의 색상을 결정하고, 
// 이후 블렌딩 연산을 거쳐 최종적인 픽셀 색상을 렌더 타겟에 저장
// 
// 
// ==================
// Output Merge State
// ==================
// DepthStencil State
// Blend State
// 
// 최종 출력
// RenderTarget
// DepthStencilTexture
//


CMesh* RectMesh = nullptr;
CMesh* CircleMesh = nullptr;

// 상수버퍼(ConstantBuffer): 물체의 위치, 크기, 회전 (transform)
ComPtr<ID3D11Buffer> ConstantBuffer;

// 정점 하나를 구성하는 Layout 정보
ComPtr<ID3D11InputLayout> Layout;

// System Mem 정점 정보
Vertex VtxArr[4] = {};

// 물체의 위치값
Vector3 ObjectPos;

// Vertex Shader
ComPtr<ID3DBlob>			VS_Blob;	// 컴파일한 쉐이더 코드를 저장
ComPtr<ID3D11VertexShader>	VS;			// Vertex Shader

// Pixel Shader
ComPtr<ID3DBlob>			PS_Blob;	// 컴파일한 쉐이더 코드를 저장
ComPtr<ID3D11PixelShader>	PS;			// Pixel Shader

// Error Bolb
ComPtr<ID3DBlob>			Err_Blob;

int TempInit()
{
	// 사각형 그리기
	VtxArr[0].vPos = Vector3(-.5f,  .5f, 0.f);
	VtxArr[1].vPos = Vector3( .5f,  .5f, 0.f);
	VtxArr[2].vPos = Vector3( .5f, -.5f, 0.f);
	VtxArr[3].vPos = Vector3(-.5f, -.5f, 0.f);

	VtxArr[0].vColor = Vector4(1.f, 0.f, 0.f, 1.f);
	VtxArr[1].vColor = Vector4(0.f, 1.f, 0.f, 1.f);
	VtxArr[2].vColor = Vector4(0.f, 0.f, 1.f, 1.f);
	VtxArr[3].vColor = Vector4(1.f, 1.f, 1.f, 1.f);

	UINT arrIdx[6] = { 0, 1, 2, 0, 2, 3 };

	RectMesh = new CMesh;
	RectMesh->Create(VtxArr, 4, arrIdx, 6);


	// ConstantBuffer
	D3D11_BUFFER_DESC ConstantBufferDesc = {};
	ConstantBufferDesc.ByteWidth = sizeof(Transform);
	ConstantBufferDesc.MiscFlags = 0;

	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER; // 만들어질때 용도(Constant) 지정
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	D3D11_SUBRESOURCE_DATA SubDesc = {};
	SubDesc.pSysMem = arrIdx;

	if (FAILED(_DEVICE->CreateBuffer(&ConstantBufferDesc, nullptr, ConstantBuffer.GetAddressOf())))
	{
		return E_FAIL;
	}


	// Vertex Shader
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += L"shader\\std2d.fx";

	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "VS_Std2D", "vs_5_0", D3DCOMPILE_DEBUG, 0
		, VS_Blob.GetAddressOf(), Err_Blob.GetAddressOf())))
	{
		if (nullptr != Err_Blob)
		{
			MessageBoxA(nullptr
				, (char*)Err_Blob->GetBufferPointer()
				, "버텍스 쉐이더 컴파일 오류", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"파일을 찾을 수 없다"
				, L"버텍스 쉐이더 컴파일 오류", MB_OK);
		}
		return E_FAIL;
	}

	if (FAILED(_DEVICE->CreateVertexShader(VS_Blob->GetBufferPointer()
		, VS_Blob->GetBufferSize(), nullptr, VS.GetAddressOf())))
	{
		return E_FAIL;
	}

	// 정점 Layout 정보 생성
	D3D11_INPUT_ELEMENT_DESC LayoutDesc[2] = {};
	LayoutDesc[0].AlignedByteOffset = 0;
	LayoutDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	LayoutDesc[0].InputSlot = 0;
	LayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[0].InstanceDataStepRate = 0;
	LayoutDesc[0].SemanticIndex = 0;
	LayoutDesc[0].SemanticName = "POSITION";

	//LayoutDesc[1].AlignedByteOffset = 12;
	LayoutDesc[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;

	LayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	LayoutDesc[1].InputSlot = 0;
	LayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	LayoutDesc[1].InstanceDataStepRate = 0;
	LayoutDesc[1].SemanticIndex = 0;
	LayoutDesc[1].SemanticName = "COLOR";


	if (FAILED(_DEVICE->CreateInputLayout(LayoutDesc, 2,
		VS_Blob->GetBufferPointer(), VS_Blob->GetBufferSize(),
		Layout.GetAddressOf())))
	{
		return E_FAIL;
	}

	// Pixel Shader
	if (FAILED(D3DCompileFromFile(strPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, "PS_Std2D", "ps_5_0", D3DCOMPILE_DEBUG, 0
		, PS_Blob.GetAddressOf(), Err_Blob.GetAddressOf())))
	{
		if (nullptr != Err_Blob)
		{
			MessageBoxA(nullptr
				, (char*)Err_Blob->GetBufferPointer()
				, "픽셀 쉐이더 컴파일 오류", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"파일을 찾을 수 없다"
				, L"픽셀 쉐이더 컴파일 오류", MB_OK);
		}
		return E_FAIL;
	}

	if (FAILED(_DEVICE->CreatePixelShader(PS_Blob->GetBufferPointer(),
		PS_Blob->GetBufferSize(),
		nullptr, PS.GetAddressOf())))
	{
		return E_FAIL;
	}

	ObjectPos = Vector3(0.f, 0.f, 0.f);


	return S_OK;
}

void TempReleas()
{
	if (nullptr != RectMesh)
		delete RectMesh;
}

void TempTick()
{
	float DT = CTimeMgr::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		ObjectPos.y += 1.f * DT;
	}
	if (KEY_PRESSED(KEY::S))
	{
		ObjectPos.y -= 1.f * DT;
	}
	if (KEY_PRESSED(KEY::A))
	{
		ObjectPos.x -= 1.f * DT;
	}
	if (KEY_PRESSED(KEY::D))
	{
		ObjectPos.x += 1.f * DT;
	}

	// SysMem -> GPU
	D3D11_MAPPED_SUBRESOURCE tSub = {};
	_CONTEXT->Map(ConstantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &tSub);

	Transform trans = {};
	trans.Position = ObjectPos;
	memcpy(tSub.pData, &trans, sizeof(trans));
	_CONTEXT->Unmap(ConstantBuffer.Get(), 0);

	_CONTEXT->VSSetConstantBuffers(0, 1, ConstantBuffer.GetAddressOf());
}

void TempRender()
{


	_CONTEXT->IASetInputLayout(Layout.Get());
	_CONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_CONTEXT->VSSetShader(VS.Get(), nullptr, 0);
	_CONTEXT->PSSetShader(PS.Get(), nullptr, 0);

	RectMesh->Render();
	
}
