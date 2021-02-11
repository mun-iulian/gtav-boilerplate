#include "../main.h"

WNDPROC InputHandler::oWndProc = nullptr;
tSetCursorPos InputHandler::oSetCursorPos = nullptr;

int InputHandler::Initialize(HWND hWindow)
{
	oWndProc = (WNDPROC)SetWindowLongPtr(hWindow, GWLP_WNDPROC, (__int3264)(LONG_PTR)InputHandler::WndProc);
	
	/*oSetCursorPos = (tSetCursorPos)GetProcAddress(GetModuleHandle(TEXT("User32.dll")), "SetCursorPos");

	std::cout << "[!] SetCursorPos: 0x" << std::hex << oSetCursorPos << std::endl;

	memory::hooking::detour::create("SetCursorPos", (uintptr_t)oSetCursorPos, (uintptr_t)InputHandler::SetCursorPos);
	memory::hooking::detour::enable("SetCursorPos");

	/*if (MH_CreateHook((DWORD_PTR*)InputHandler::oSetCursorPos, InputHandler::SetCursorPos, reinterpret_cast<void**>(&InputHandler::oSetCursorPos)) != MH_OK) { return 1; }
	if (MH_EnableHook((DWORD_PTR*)InputHandler::oSetCursorPos) != MH_OK) { return 1; } */

	return 1;
}

void InputHandler::Remove(HWND hWindow)
{
	SetWindowLongPtr(hWindow, GWLP_WNDPROC, (LONG_PTR)oWndProc);
}

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT APIENTRY InputHandler::WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (MenuHandler::IsOpen() && ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		return 1l;

	return CallWindowProc(oWndProc, hwnd, uMsg, wParam, lParam);
}

BOOL InputHandler::SetCursorPos(int x, int y)
{
	if (MenuHandler::IsOpen())
	{
		return true;
	}

	return InputHandler::oSetCursorPos(x, y);
}