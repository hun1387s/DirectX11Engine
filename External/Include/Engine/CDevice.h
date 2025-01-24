#pragma once


class CDevice
{
private:
	HWND							MainWnd;
	POINT							RenderResolution;

	
	ComPtr<ID3D11Device>			Device;				// GPU 메모리할당, DX11 관련 객체생성
	ComPtr<ID3D11DeviceContext>		Context;			// GPU 렌더링 관련 명령
	ComPtr<IDXGISwapChain>			SwapChain;			// 렌더타겟 버퍼 소유, 화면에 최종 장면을 게시

	ComPtr<ID3D11Texture2D>			RenderTargetTex;
	ComPtr<ID3D11RenderTargetView>	RenderTargetView;
	ComPtr<ID3D11Texture2D>			DepthStencilTex;
	ComPtr<ID3D11DepthStencilView>	DepthStencilView;

private:
	int CreateSwapChain();
	int CreateView();

public:
	static CDevice* GetInst()
	{
		static CDevice mgr;
		return &mgr;
	}
public:
	int init(HWND _hwnd, POINT _Resolution);



private:
	CDevice();
	CDevice(const CDevice& _other) = delete;

public:
	~CDevice();
};

