#pragma once

class RenderHandler {
public:
	static HWND						g_hWnd;
	static ID3D11Device*			g_pD3DDevice;
	static ID3D11DeviceContext*		g_pD3DDeviceContext;
	static IDXGISwapChain*			g_pSwapChain;
	static ID3D11RenderTargetView*	g_pRenderTargetView;
	
	static bool						CreateDevice(HWND hWnd);
	static void						CleanDevice();
	static void						CreateRenderTarget();
	static void						CleanRenderTarget();

	static LRESULT WINAPI			WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};