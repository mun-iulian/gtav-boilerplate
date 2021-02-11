#pragma once

namespace memory
{
	namespace operations
	{
		template<typename ValueType, typename AddressType>
		inline void patch(AddressType dst, ValueType value, uint16_t length = 0) {
			DWORD dProtection;

			uint16_t patchSize = length;
			if (length == 0) patchSize = sizeof(length);

			VirtualProtect((void*)dst, patchSize, PAGE_READWRITE, &dProtection);

			memcpy((void*)dst, &value, patchSize);

			VirtualProtect((void*)dst, patchSize, dProtection, &dProtection);
		}

		template<typename AddressType>
		inline void nop(AddressType address, uint16_t length)
		{
			if (length <= 0)
				return;

			DWORD dProtection;
			VirtualProtect((void*)address, length, PAGE_READWRITE, &dProtection);

			memset((void*)address, 0x90, length);

			VirtualProtect((void*)address, length, dProtection, &dProtection);
		}

		template<typename AddressType>
		inline void ret(AddressType address, uint16_t stackSize = 0)
		{
			if (stackSize == 0)
			{
				patch<uint8_t>(address, 0xC3);
			}
			else
			{
				patch<uint8_t>(address, 0xC2);
				patch<uint16_t>((uintptr_t)address + 1, stackSize);
			}
		}

		//TODO: de testat functiile jump si call
		template<typename FunctionType, typename AddressType>
		inline void jump(AddressType address, FunctionType func, uint16_t length)
		{
			patch<uint8_t>(address, 0xE9);
			patch<int>((uintptr_t)address + 1, (intptr_t)func - (intptr_t)address - 5);

			size_t jumpSize = (sizeof(intptr_t) + 1);
			nop((uintptr_t)address + jumpSize + 1, length - jumpSize);
		}
	
		template<typename FunctionType, typename AddressType>
		inline void call(AddressType address, FunctionType func, uint16_t length)
		{
			patch<uint8_t>(address, 0xE8);
			patch<int>((uintptr_t)address + 1, (intptr_t)func - (intptr_t)address - 5);

			size_t jumpSize = (sizeof(intptr_t) + 1);
			nop((uintptr_t)address + jumpSize + 1, length - jumpSize);
		}

		template<typename AddressType>
		inline AddressType get_call(AddressType address)
		{
			intptr_t target = *(uintptr_t*)(address + 1);
			target += (address + 5);

			return (AddressType)target;
		}
	}
}