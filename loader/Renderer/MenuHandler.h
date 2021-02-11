#pragma once

class MenuHandler {
public:
	static bool IsOpen() { return m_IsOpen; }
	static void Render();
	static void Initialize();
	static void Begin();
	static void End();

private:
	static bool m_IsOpen;
	static const ImVec2 m_Size;
};