#include "../main.h"


namespace memory
{
	uintptr_t pattern::check_map(const std::string& pattern)
	{
		if (pattern::offsets.find(pattern) != pattern::offsets.end()) {
			return pattern::offsets.find(pattern)->second;
		}

		return NULL;
	}

	bool pattern::check_offset(const std::string& pattern, const std::string& mask, uintptr_t offset) {

		const char* cPattern = pattern.c_str();
		const char* cMask = mask.c_str();

		char* ptr = reinterpret_cast<char*>(offset);

		for (size_t i = 0; i < pattern.size(); i++) {

			if (cMask[i] == '?') {
				continue;
			}

			if (cPattern[i] != ptr[i]) {
				return false;
			}
		}

		return true;
	}

	void pattern::transform_pattern(const std::string& pattern, std::string& data, std::string& mask) {

		std::stringstream dataStr;
		std::stringstream maskStr;

		uint8_t tempDigit = 0;
		bool tempFlag = false;

		for (auto& ch : pattern) {

			if (ch == ' ') {
				continue;
			}
			else if (ch == '?') {

				dataStr << '\x00';
				maskStr << '?';
			}
			else if ((ch >= '0' && ch <= '9') || (ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f')) {

				char str[] = { ch, 0 };
				int thisDigit = strtol(str, nullptr, 16);

				if (!tempFlag) {

					tempDigit = (thisDigit << 4);
					tempFlag = true;
				}
				else {

					tempDigit |= thisDigit;
					tempFlag = false;

					dataStr << tempDigit;
					maskStr << 'x';
				}
			}
		}

		data = dataStr.str();
		mask = maskStr.str();
	}

	template<typename pointerType>
	pointerType pattern::find_pattern(const std::string& pattern, const std::string& mask, size_t length, void* start, void* end)
	{
		uintptr_t mapPtr = check_map(pattern);
		if (mapPtr != NULL)
			return mapPtr;

		std::string baseString(pattern, length);
		std::string m_bytes, m_mask(mask);

		// transform the base pattern from IDA format to canonical format
		pattern::transform_pattern(baseString, m_bytes, m_mask);

		for (uintptr_t i = (uintptr_t)start; i <= (uintptr_t)end; i++) {

			if (pattern::check_offset(m_bytes, m_mask, i)) {
				pattern::offsets.insert(std::make_pair(pattern, i));
				return i;
			}
		}
	}

	template<typename pointerType>
	pointerType pattern::find_pattern(const std::string& pattern, const std::string& mask, size_t length, const char* moduleName)
	{
		MODULEINFO mInfo;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleW((LPCWSTR)moduleName), &mInfo, sizeof(MODULEINFO));

		return pattern::find_pattern<pointerType>(pattern, mask, length, mInfo.lpBaseOfDll, mInfo.lpBaseOfDll + mInfo.SizeOfImage);
	}

	template<typename pointerType>
	pointerType pattern::find_pattern(const std::string& pattern, const std::string& mask, size_t length)
	{
		return pattern::find_pattern<pointerType>(pattern, mask, length, NULL);
	}
}