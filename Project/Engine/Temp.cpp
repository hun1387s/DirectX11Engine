#include "pch.h"
#include "Temp.h"

#include "CDevice.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CMesh.h"
#include "CConstBuffer.h"
#include "CGraphicShader.h"


// Mesh
Ptr<CMesh> RectMesh = nullptr;
Ptr<CMesh> CircleMesh = nullptr;

// Shader
Ptr<CGraphicShader> Shader = nullptr;


// System Mem 정점 정보
Vertex VtxArr[4] = {};

// 물체의 위치, 크기, 회전
Transform transform = {};


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

	
	// Create Shader
	wstring strPath = CPathMgr::GetInst()->GetContentPath();
	strPath += L"shader\\std2d.fx";

	Shader = new CGraphicShader;
	Shader->CreateVertexShader(strPath, "VS_Std2D");
	Shader->CreatePixelShader(strPath, "PS_Std2D");
	

	return S_OK;
}

void TempReleas()
{

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
	Shader->Binding();

	//RectMesh->Render();
	CircleMesh->Render();
}
