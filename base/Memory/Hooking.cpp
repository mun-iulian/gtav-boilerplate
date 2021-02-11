#include "../main.h"


namespace memory
{
	namespace hooking
	{
		void create(std::string name, uintptr_t target, uintptr_t detour, hook_type type)
		{
			uintptr_t fixed_target = target;
			std::cout << "Fixed target: " << std::hex << fixed_target;

			hook_data current_hook = hook_data(name, target, fixed_target, detour, type);

			if (auto status = MH_CreateHook((void*)fixed_target, (void*)detour, &current_hook.original_bytes); status == MH_OK) {
				Log::Message("Successfully hooked %s.", name);
				detour_vec.push_back(current_hook);
			} else
				Log::Error("Failed to hook 0x%X (%s)", target, MH_StatusToString(status));
		}

		uintptr_t fix_address(uintptr_t address)
		{
			auto ptr = address;

			while (*(BYTE*)ptr == 0xE9)
			{
				ptr = *(uintptr_t*)(ptr + 1);
			}

			return ptr;
		}

		hook_data get(std::string name)
		{
			for (auto i : detour_vec)
			{
				if (i.name != name)
					continue;

				return i;
			}
		}
		hook_data get(uintptr_t target)
		{
			for (auto i : detour_vec)
			{
				if (i.target != target)
					continue;

				return i;
			}
		}

		void enable(std::string name)
		{
			for (auto i : detour_vec)
			{
				if (i.name != name)
					continue;
					
				if (MH_EnableHook((void*)i.fixed_target) == MH_OK)
					Log::Message("Successfully enabled hook '%s'.", i.name);
				else
					Log::Message("Failed to enable hook '%s'.", i.name);
			}
		}
		void enable(uintptr_t target)
		{
			for (auto i : detour_vec)
			{
				if (i.target != target)
					continue;

				if (MH_EnableHook((void*)i.fixed_target) == MH_OK)
					Log::Message("Successfully enabled hook '%s'.", i.name);
				else
					Log::Message("Failed to enable hook '%s'.", i.name);
			}
		}
		void enable(hook_type type)
		{
			for (auto i : detour_vec)
			{
				if (i.type != type && type != HOOK_ALL)
					continue;

				if (MH_EnableHook((void*)i.fixed_target) == MH_OK)
					Log::Message("Successfully enabled hook '%s'.", i.name);
				else
					Log::Message("Failed to enable hook '%s'.", i.name);
			}
		}

		void disable(std::string name)
		{
			for (auto i : detour_vec)
			{
				if (i.name != name)
					continue;

				if (MH_DisableHook((void*)i.fixed_target) == MH_OK)
					Log::Message("Successfully disabled hook '%s'.", i.name);
				else
					Log::Message("Failed to disable hook '%s'.", i.name);
			}
		}
		void disable(uintptr_t target)
		{
			for (auto i : detour_vec)
			{
				if (i.target != target)
					continue;

				if (MH_DisableHook((void*)i.fixed_target) == MH_OK)
					Log::Message("Successfully disabled hook '%s'.", i.name);
				else
					Log::Message("Failed to disable hook '%s'.", i.name);
			}
		}
		void disable(hook_type type)
		{
			for (auto i : detour_vec)
			{
				if (i.type != type && type != HOOK_ALL)
					continue;

				if (MH_DisableHook((void*)i.fixed_target) == MH_OK)
					Log::Message("Successfully disabled hook '%s'.", i.name);
				else
					Log::Message("Failed to disable hook '%s'.", i.name);
			}
		}

		void remove(std::string name)
		{
			for (auto i : detour_vec)
			{
				if (i.name != name)
					continue;

				if (MH_RemoveHook((void*)i.fixed_target) == MH_OK)
					Log::Message("Successfully removed hook '%s'.", i.name);
				else
					Log::Message("Failed to remove hook '%s'.", i.name);
			}
		}
		void remove(uintptr_t target)
		{
			for (auto i : detour_vec)
			{
				if (i.target != target)
					continue;

				if (MH_RemoveHook((void*)i.fixed_target) == MH_OK)
					Log::Message("Successfully removed hook '%s'.", i.name);
				else
					Log::Message("Failed to remove hook '%s'.", i.name);
			}
		}
		void remove(hook_type type)
		{
			for (auto i : detour_vec)
			{
				if (i.type != type && type != HOOK_ALL)
					continue;

				if (MH_RemoveHook((void*)i.fixed_target) == MH_OK)
					Log::Message("Successfully removed hook '%s'.", i.name);
				else
					Log::Message("Failed to remove hook '%s'.", i.name);
			}
		}


		
	}
}