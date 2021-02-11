#include "../main.h"

#include <mutex>

tPresentHook			RenderHandler::oPresentHook = nullptr;
HWND					RenderHandler::g_hWnd = nullptr;
HMODULE					RenderHandler::g_hModule = nullptr;
ID3D11Device*			RenderHandler::g_pD3DDevice = nullptr;
ID3D11DeviceContext*	RenderHandler::g_pD3DContext = nullptr;
IDXGISwapChain*			RenderHandler::g_pSwapChain = nullptr;

DWORD_PTR*				RenderHandler::pSwapChainVT = NULL;
DWORD_PTR*				RenderHandler::pContextVT = NULL;
DWORD_PTR*				RenderHandler::pDeviceVT = NULL;


HRESULT __stdcall RenderHandler::PresentHook(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
{

	std::call_once(GraphicHandler::g_isInitialized, [&]() {
		pSwapChain->GetDevice(__uuidof(g_pD3DDevice), reinterpret_cast<void**>(&g_pD3DDevice));
		g_pD3DDevice->GetImmediateContext(&g_pD3DContext);

		GraphicHandler::Initialize(g_pD3DDevice, g_pD3DContext, g_hWnd);
		InputHandler::Initialize(g_hWnd);
	});

	MenuHandler::Listen();

	GraphicHandler::Begin();
	MenuHandler::Render();
	GraphicHandler::End();

	return RenderHandler::oPresentHook(pSwapChain, SyncInterval, Flags);
}

DWORD __stdcall RenderHandler::InitHook()
{
	D3D_FEATURE_LEVEL requestedLevels[] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1 };
	D3D_FEATURE_LEVEL obtainedLevel;
	DXGI_SWAP_CHAIN_DESC scd;
	ZeroMemory(&scd, sizeof(scd));
	scd.BufferCount = 1;
	scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	scd.OutputWindow = g_hWnd;
	scd.SampleDesc.Count = 1; // Set to 1 to disable multisampling
	scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	scd.Windowed = true;

	scd.BufferDesc.Width = 1;
	scd.BufferDesc.Height = 1;
	scd.BufferDesc.RefreshRate.Numerator = 0;
	scd.BufferDesc.RefreshRate.Denominator = 1;

	if (FAILED(D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		requestedLevels,
		sizeof(requestedLevels) / sizeof(D3D_FEATURE_LEVEL),
		D3D11_SDK_VERSION,
		&scd,
		&g_pSwapChain,
		&g_pD3DDevice,
		&obtainedLevel,
		&g_pD3DContext))) {
			return NULL;
	}

	RenderHandler::pSwapChainVT = (DWORD_PTR*)(RenderHandler::g_pSwapChain);
	RenderHandler::pSwapChainVT = (DWORD_PTR*)(RenderHandler::pSwapChainVT[0]);

	RenderHandler::pDeviceVT = (DWORD_PTR*)(RenderHandler::g_pD3DDevice);
	RenderHandler::pDeviceVT = (DWORD_PTR*)RenderHandler::pDeviceVT[0];

	RenderHandler::pContextVT = (DWORD_PTR*)(RenderHandler::g_pD3DContext);
	RenderHandler::pContextVT = (DWORD_PTR*)(RenderHandler::pContextVT[0]);

	std::cout << "[!] Present: 0x" << std::hex << RenderHandler::pSwapChainVT[8] << std::endl;

	if (MH_Initialize() != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)RenderHandler::pSwapChainVT[8], RenderHandler::PresentHook, reinterpret_cast<void**>(&RenderHandler::oPresentHook)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)RenderHandler::pSwapChainVT[8]) != MH_OK) { return 1; }
}

void RenderHandler::Initialize(HMODULE hModule, HWND hWnd)
{
	RenderHandler::g_hWnd = hWnd;
	RenderHandler::g_hModule = hModule;
	RenderHandler::InitHook();
}

void RenderHandler::Shutdown()
{
	InputHandler::Remove(g_hWnd);

	g_pD3DDevice->Release();
	g_pD3DContext->Release();
	g_pSwapChain->Release();

	if (MH_DisableHook(MH_ALL_HOOKS)) { return; };
	if (MH_Uninitialize()) { return; }
}