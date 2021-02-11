#include "main.h"

int APIENTRY wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
    // Create application window
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, RenderHandler::WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "DELUXE", NULL };
    RegisterClassEx(&wc);
    RenderHandler::g_hWnd = CreateWindow(wc.lpszClassName, "DELUXE", WS_POPUP, 0, 0, 5, 5, NULL, NULL, wc.hInstance, NULL);

    // Initialize Direct3D
    if (!RenderHandler::CreateDevice(RenderHandler::g_hWnd)) {
        RenderHandler::CleanDevice();
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        return 1;
    }

    // Show the window
    ShowWindow(RenderHandler::g_hWnd, SW_HIDE);
    UpdateWindow(RenderHandler::g_hWnd);

    // Setup Dear ImGui context
    MenuHandler::Initialize();

    // Main loop
    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT)
    {
        if (::PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            ::TranslateMessage(&msg);
            ::DispatchMessage(&msg);
            continue;
        }

        // Start the Dear ImGui frame
        MenuHandler::Begin();

        MenuHandler::Render();

        // Rendering
        MenuHandler::End();


        if (!MenuHandler::IsOpen())
            msg.message = WM_QUIT;
    }

    // Cleanup
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    RenderHandler::CleanDevice();
    DestroyWindow(RenderHandler::g_hWnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    return 0;
}