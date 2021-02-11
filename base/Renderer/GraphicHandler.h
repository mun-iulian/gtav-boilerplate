#pragma once


class GraphicHandler {
public:
	static void					Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, void* hWnd);
	static void					Begin();
	static void					End();

	static std::once_flag		g_isInitialized;
};