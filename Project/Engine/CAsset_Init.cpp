#include "pch.h"
#include "CAssetMgr.h"
#include "CPathMgr.h"


void CAssetMgr::init()
{
	CreateDefaultMesh();
	CreateDefaultTexture();
	CreateDefaultMaterial();
	CreateDefaultGraphicShader();
	CreateDefaultComputShader();
}

void CAssetMgr::CreateDefaultMesh()
{

	Ptr<CMesh> mesh = nullptr;

	vector<Vertex> vecVtx;
	vector<UINT> vecIdx;
	Vertex v;


	// ============
	// 사각형 그리기
	// ============
	v.vPos = Vector3(-.5f, .5f, 0.f);
	v.vColor = Vector4(1.f, 0.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vector3(.5f, .5f, 0.f);
	v.vColor = Vector4(0.f, 1.f, 0.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vector3(.5f, -.5f, 0.f);
	v.vColor = Vector4(0.f, 0.f, 1.f, 1.f);
	vecVtx.push_back(v);

	v.vPos = Vector3(-.5f, -.5f, 0.f);
	v.vColor = Vector4(1.f, 1.f, 1.f, 1.f);
	vecVtx.push_back(v);

	vecIdx.push_back(0);
	vecIdx.push_back(1);
	vecIdx.push_back(2);
	vecIdx.push_back(0);
	vecIdx.push_back(2);
	vecIdx.push_back(3);
	

	mesh = new CMesh;
	mesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset<CMesh>(L"RectMesh", mesh.Get());
	vecVtx.clear();
	vecIdx.clear();

	// ============
	//   원 그리기
	// ============


	// 원점 v 초기화(vector에 넣는다)
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

	mesh = new CMesh;
	mesh->Create(vecVtx.data(), (UINT)vecVtx.size(), vecIdx.data(), (UINT)vecIdx.size());
	AddAsset<CMesh>(L"CircleMesh", mesh);
	vecVtx.clear();
	vecIdx.clear();
}

void CAssetMgr::CreateDefaultTexture()
{
}

void CAssetMgr::CreateDefaultMaterial()
{
}

void CAssetMgr::CreateDefaultGraphicShader()
{
	Ptr<CGraphicShader> shader = nullptr;

	// Create Shader
	wstring strPath = CPathMgr::GetInst()->GetContentPath();

	shader = new CGraphicShader;
	shader->CreateVertexShader(strPath + L"shader\\std2d.fx", "VS_Std2D");
	shader->CreatePixelShader(strPath + L"shader\\std2d.fx", "PS_Std2D");

	AddAsset<CGraphicShader>(L"Std2DShader", shader);

}

void CAssetMgr::CreateDefaultComputShader()
{
}
