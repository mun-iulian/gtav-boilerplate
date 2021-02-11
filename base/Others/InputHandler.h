#pragma once

typedef BOOL(__stdcall* tSetCursorPos) (int, int);

class InputHandler
{
public:
	static int					Initialize(HWND hWindow);
	static void					Remove(HWND hWindow);

private:
	static LRESULT APIENTRY		WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	static WNDPROC				oWndProc;

	static BOOL					SetCursorPos(int x, int y);
	static tSetCursorPos		oSetCursorPos;
};