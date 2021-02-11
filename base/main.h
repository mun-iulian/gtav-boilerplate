#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

#include <DXGI.h>
#include <d3d11.h>


#include "../dependencies/minhook/include/MinHook.h"

#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_internal.h"
#include "../dependencies/imgui/imgui_impl_dx11.h"
#include "../dependencies/imgui/imgui_impl_win32.h"


#include "./Memory/Memory.h"

#include "./Others/Log.h"
#include "./Others/InputHandler.h"

#include "./Renderer/MenuHandler.h"
#include "./Renderer/RenderHandler.h"
#include "./Renderer/GraphicHandler.h"
