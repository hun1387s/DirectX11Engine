#include "pch.h"
#include "CDevice.h"


CDevice::CDevice()
	: MainWnd(nullptr)
	, RenderResolution{}
{
}

CDevice::~CDevice()
{
}


int CDevice::init(HWND _hwnd, POINT _Resolution)
{
	MainWnd = _hwnd;					// 렌더링 대상 윈도우 핸들
	RenderResolution = _Resolution;		// 렌더링 해상도

	UINT flag = 0;						// 디바이스 생성 옵션 플래그
#ifdef _DEBUG
	flag = D3D11_CREATE_DEVICE_DEBUG;	// 디버그 모드로 디바이스 생성
#endif

	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_11_0;		// 시용할 D3D 기능 레벨지정

	if (FAILED(D3D11CreateDevice(
		nullptr,					// 기본 어댑터
		D3D_DRIVER_TYPE_HARDWARE,	// 하드웨어 가속
		nullptr,					// 소프트웨어 드라이버 사용 안함
		flag,						// 플래그(디버그)
		nullptr,					// 기능 레벨 배열 없음
		0,							// 배열 갯수
		D3D11_SDK_VERSION,			// SDK 버전
		Device.GetAddressOf(),		// 생성된 디바이스
		&level,						// 실제 생성된 기능 레벨
		Context.GetAddressOf())))	// 생성된 컨텍스트
	{
		// 실패시 종료
		MessageBox(nullptr, L"Device 생성 실패", L"Device 생성 실패", MB_OK);
		return E_FAIL;
	}

	// SwapChain 생성
	if (FAILED(CreateSwapChain()))
	{
		// 실패시 종료
		MessageBox(nullptr, L"SwapChain 생성 실패", L"SwapChain 생성 실패", MB_OK);
		return E_FAIL;
	}

	// View 생성
	if (FAILED(CreateView()))
	{
		// 실패시 종료
		MessageBox(nullptr, L"View 생성 실패", L"View 생성 실패", MB_OK);
		return E_FAIL;
	}

	// ViewPort 설정
	// 윈도우 화면에 보여질 영역 설정
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = RenderResolution.x;
	viewport.Height = RenderResolution.y;

	// 깊이 텍스쳐에 저장되는 깊이 min max 지정
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;

	// ViewPort 정보 세팅
	Context->RSSetViewports(1, &viewport);


	// 정상 종료
	return S_OK;
}

void CDevice::ClearTarget(float(&ArrColor)[4])
{
	Context->ClearRenderTargetView(RenderTargetView.Get(), ArrColor);
}


int CDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC Desc = {};

	// SwapChain이 화면을 게시(Present) 할때 출력 목적지 윈도우
	// SwapChain 생성 정보 초기화
	Desc.OutputWindow = MainWnd; // 출력 대상 윈도우
	Desc.Windowed = true;		 // 창 모드 사용

	// SwapChain이 만들어질 때 버퍼 옵션
	// 백버퍼 설정
	Desc.BufferCount = 1; // 백버퍼 수
	Desc.BufferDesc.Width = (UINT)RenderResolution.x;		// 버퍼 너비
	Desc.BufferDesc.Height = (UINT)RenderResolution.y;		// 버퍼 높이
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	// 색상 포맷
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;		// 렌더 타겟 용도
	// 디스플레이 모드 설정
	Desc.BufferDesc.RefreshRate.Denominator = 1;	// Refresh 분모
	Desc.BufferDesc.RefreshRate.Numerator = 60;		// Refresh 분자
	Desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;	// 스케일링 없음
	Desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;	// 스캔 라인 순서 없음

	// 멀치 샘플링 설정
	Desc.SampleDesc.Count = 1;		// 샘플 갯수
	Desc.SampleDesc.Quality = 0;	// 샘플 품질

	// SwapChain 이펙트 설정.
	// 1. 비트 블록 전송 모델
	// DXGI_SWAP_EFFECT_DISCARD
	// DXGI_SWAP_EFFECT_SEQUENTIAL
	// 2. 대칭 이동 프레젠테이션 모델
	// DXGI_SWAP_EFFECT_FLIP_DISCARD
	// DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL
	Desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	// DXGI 인터페이스 획득
	ComPtr<IDXGIDevice> DXGIDevice = nullptr;
	ComPtr<IDXGIAdapter> Adatper = nullptr;
	ComPtr<IDXGIFactory> Factory = nullptr;

	// Device에서 DXGIDevice 인터페이스 획득
	Device->QueryInterface(__uuidof(IDXGIDevice), (void**)DXGIDevice.GetAddressOf());
	// DXGIDevice에서 상위 Adapter 인터페이스 획득
	DXGIDevice->GetParent(__uuidof(IDXGIAdapter), (void**)Adatper.GetAddressOf());
	// Adepter에서 상위 Factory 인터페이스 획득
	Adatper->GetParent(__uuidof(IDXGIFactory), (void**)Factory.GetAddressOf());

	// SwapChain 생성 시도
	if (FAILED(Factory->CreateSwapChain(Device.Get(), &Desc, SwapChain.GetAddressOf())))
	{
		// 실패 시 반환
		return	E_FAIL;
	}

	return S_OK;
}

int CDevice::CreateView()
{
	// 1. RenderTarget Texture를 SwapChain으로부터 가져오기
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)RenderTargetTex.GetAddressOf());

	// 2. RenderTargetView를 생성한다.
	Device->CreateRenderTargetView(RenderTargetTex.Get(), nullptr, RenderTargetView.GetAddressOf());

	// 3. DepthStencil용 Texture 제작
	D3D11_TEXTURE2D_DESC Desc = {};

	// Depth 25bit, Stencil 8Bit
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	// 렌더타겟과 해상도 일치
	Desc.Width = (UINT)RenderResolution.x;
	Desc.Height = (UINT)RenderResolution.y;
	Desc.ArraySize = 1;					// 배열크기
	Desc.CPUAccessFlags = 0;			// CPU 접근 없음
	Desc.Usage = D3D11_USAGE_DEFAULT;	// 기본사용
	Desc.MipLevels = 1;
	Desc.SampleDesc.Count = 1;			// 멀티 샘플링 비활성
	Desc.SampleDesc.Quality = 0;		// 품질 설정
	// 텍스쳐 용도설정(깊이를 저장하는 전용 명시)
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;

	Device->CreateTexture2D(&Desc, nullptr, DepthStencilTex.GetAddressOf());

	// 4. DepthStencil View
	Device->CreateDepthStencilView(DepthStencilTex.Get(), nullptr, DepthStencilView.GetAddressOf());

	// RenderTarget과 DepthStencilTarget을 출력으로 지정.
	Context->OMSetRenderTargets(1, RenderTargetView.GetAddressOf(), DepthStencilView.Get());




	return S_OK;
}
