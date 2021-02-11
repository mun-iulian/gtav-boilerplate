#pragma once

class MenuHandler {
public:
	static void		Render();
	static void		Listen();
	static bool		IsOpen() { return m_IsOpen; }

private:
	static bool		m_IsOpen;
	static int		m_OpenKey;

};