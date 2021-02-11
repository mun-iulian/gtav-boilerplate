#pragma once

#include <map>

namespace memory
{
	namespace hooking
	{
		enum hook_type { //for bulk enabling/disabling/creation (disables all render hooks, disables all input hooks, etc.)
			HOOK_NONE,
			HOOK_RENDER,
			HOOK_INPUT,

			HOOK_ALL = 1337  //used to enable/disable/remove all hooks
		};

		struct hook_data {

			hook_data() {
				this->name = nullptr;
				this->original_bytes = nullptr;
				this->target = NULL;
				this->fixed_target = NULL;
				this->detour = NULL;
				this->type = HOOK_NONE;
			}

			hook_data(std::string name, uintptr_t target, uintptr_t fixed_target, uintptr_t detour, hook_type type)
			{
				this->name = name;
				this->target = target;
				this->fixed_target = fixed_target;
				this->detour = detour;
				this->type = type;
				this->original_bytes = nullptr;
			}

			std::string name;
			void* original_bytes{};
			uintptr_t target;
			uintptr_t fixed_target;
			uintptr_t detour;
			hook_type type;
		};

		inline std::vector<hook_data> detour_vec;

		void			create(std::string name, uintptr_t target, uintptr_t detour, hook_type type = HOOK_NONE);
		uintptr_t		fix_address(uintptr_t address);

		hook_data		get(std::string name);
		hook_data		get(uintptr_t target);

		void			enable(std::string name);
		void			enable(uintptr_t target);
		void			enable(hook_type type);

		void			disable(std::string name);
		void			disable(uintptr_t target);
		void			disable(hook_type type);

		void			remove(std::string name);
		void			remove(uintptr_t target);
		void			remove(hook_type type);
	}
}