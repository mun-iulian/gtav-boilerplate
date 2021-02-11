#include "../main.h"

bool			MenuHandler::m_IsOpen = false;
int				MenuHandler::m_OpenKey = VK_INSERT;

void MenuHandler::Listen()
{
	if (GetAsyncKeyState(MenuHandler::m_OpenKey) & 1)
		MenuHandler::m_IsOpen = !MenuHandler::m_IsOpen;
}

void MenuHandler::Render()
{
	ImGui::GetIO().MouseDrawCursor = MenuHandler::m_IsOpen;

	if (!MenuHandler::m_IsOpen)
		return;

	ImGui::SetNextWindowSize(ImVec2(450, 600));
	ImGui::Begin("ImGui Menu", &MenuHandler::m_IsOpen);

	ImGui::Text("ImGui Window");

	ImGui::End();
}