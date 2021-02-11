#pragma once

#include <string>
#include <vector>
#include <intrin.h>
#include <sstream>
#include <psapi.h>
#include <map>

namespace memory
{
	namespace pattern {

		inline std::map<std::string, uintptr_t> offsets;

		uintptr_t			check_map(const std::string& pattern);
		bool				check_offset(const std::string& pattern, const std::string& mask, uintptr_t offset); // call transform_pattern before check_offset
		void				transform_pattern(const std::string& pattern, std::string& data, std::string& mask);

		template<typename pointerType>
		pointerType find_pattern(const std::string& pattern, const std::string& mask, size_t length, void* start, void* end); // find in custom range

		template<typename pointerType>
		pointerType find_pattern(const std::string& pattern, const std::string& mask, size_t length, const char* moduleName); // find in custom module

		template<typename pointerType>
		pointerType find_pattern(const std::string& pattern, const std::string& mask, size_t length); //find in current module
	};
}