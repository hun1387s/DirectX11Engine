#include "pch.h"
#include "CGraphicShader.h"

#include "CDevice.h"

CGraphicShader::CGraphicShader()
	: CShader(ASSET_TYPE::GRAPHICS_SHADER)
	, Topology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
}

CGraphicShader::~CGraphicShader()
{
}


int CGraphicShader::CreateVertexShader(const wstring& filePath, const string& VSfuncName)
{
	// Vertex Shader
	if (FAILED(D3DCompileFromFile(filePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, VSfuncName.c_str(), "vs_5_0", D3DCOMPILE_DEBUG, 0
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
										 , VS_Blob->GetBufferSize()
									     , nullptr, VS.GetAddressOf())))
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


	return S_OK;
}

int CGraphicShader::CreatePixelShader(const wstring& filePath, const string& PSfuncName)
{
	// Pixel Shader
	if (FAILED(D3DCompileFromFile(filePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, PSfuncName.c_str(), "ps_5_0", D3DCOMPILE_DEBUG, 0
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




void CGraphicShader::Binding()
{
	_CONTEXT->IASetInputLayout(Layout.Get());
	_CONTEXT->IASetPrimitiveTopology(Topology);

	_CONTEXT->VSSetShader(VS.Get(), nullptr, 0);
	_CONTEXT->PSSetShader(PS.Get(), nullptr, 0);
}