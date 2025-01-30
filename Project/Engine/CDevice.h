#pragma once


class CDevice
	: public CSingleton<CDevice>
{
	SINGLE(CDevice);
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
	int init(HWND _hwnd, POINT _Resolution);
	void ClearTarget(float(&ArrColor)[4]);
	void Present() { SwapChain->Present(0, 0); }

	ID3D11Device* GetDevice() { return Device.Get(); }
	ID3D11DeviceContext* GetContext() { return Context.Get(); }
};

