#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CMesh.h"
#include "CConstBuffer.h"



CMesh* RectMesh = nullptr;
CMesh* CircleMesh = nullptr;



// 정점 하나를 구성하는 Layout 정보
ComPtr<ID3D11InputLayout> Layout;

// System Mem 정점 정보
Vertex VtxArr[4] = {};

// 물체의 위치, 크기, 회전
Transform transform = {};

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
	// ============
	// 사각형 그리기
	// ============
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

	// ============
	//   원 그리기
	// ============
	vector<Vertex> vecVtx;
	vector<UINT> vecIdx;

	// 원점 v 초기화(vector에 넣는다)
	Vertex v;
	v.vPos = Vector3(0.f, 0.f, 0.f);
	v.vColor = Vector4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);


	float radius = 0.5;
	UINT slice = 40;

	float angleStep = (2 * XM_PI) / slice;

	float angle = 0.f;
	for (UINT i = 0; i <= slice; i++)
	{
		Vertex v;
		v.vPos = Vector3(cosf(angle) * radius, sinf(angle) * radius, 0.f);
		v.vColor = Vector4(1.f, 1.f, 1.f, 1.f);

		vecVtx.push_back(v);
		angle += angleStep;
	}

	for (UINT i = 0; i < slice; i++)
	{
		vecIdx.push_back(0);
		vecIdx.push_back(i + 2);
		vecIdx.push_back(i + 1);
	}

	CircleMesh = new CMesh;
	CircleMesh->Create(vecVtx.data(), vecVtx.size(), vecIdx.data(), vecIdx.size());

	


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

	return S_OK;
}

void TempReleas()
{
	if (nullptr != RectMesh)
		delete RectMesh;
	if (nullptr != CircleMesh)
		delete CircleMesh;
}

void TempTick()
{
	float DT = CTimeMgr::GetInst()->GetDeltaTime();

	if (KEY_PRESSED(KEY::W))
	{
		transform.Position.y += 1.f * DT;
	}
	if (KEY_PRESSED(KEY::S))
	{
		transform.Position.y -= 1.f * DT;
	}
	if (KEY_PRESSED(KEY::A))
	{
		transform.Position.x -= 1.f * DT;
	}
	if (KEY_PRESSED(KEY::D))
	{
		transform.Position.x += 1.f * DT;
	}

	// SysMem -> GPU
	CConstBuffer* constBuffer = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRNSFORM);
	constBuffer->SetData(&transform);
	constBuffer->Binding();


	
}

void TempRender()
{


	_CONTEXT->IASetInputLayout(Layout.Get());
	_CONTEXT->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	_CONTEXT->VSSetShader(VS.Get(), nullptr, 0);
	_CONTEXT->PSSetShader(PS.Get(), nullptr, 0);

	//RectMesh->Render();
	CircleMesh->Render();
	
}
