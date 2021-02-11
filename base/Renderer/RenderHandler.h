#pragma once

typedef HRESULT(__stdcall* tPresentHook) (IDXGISwapChain*, UINT, UINT);

class RenderHandler {
public:
	static void						Initialize(HMODULE hModule, HWND hWnd);
	static void						Shutdown();
	

private:
	static DWORD __stdcall			InitHook();
	static HRESULT __stdcall		PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);

	static HWND						g_hWnd;
	static HMODULE					g_hModule;
	static ID3D11Device*			g_pD3DDevice;
	static ID3D11DeviceContext*		g_pD3DContext;
	static IDXGISwapChain*			g_pSwapChain;

	static DWORD_PTR*				pSwapChainVT;
	static DWORD_PTR*				pContextVT;
	static DWORD_PTR*				pDeviceVT;


	static tPresentHook oPresentHook;
};