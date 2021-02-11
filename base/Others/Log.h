#pragma once


class Log {
public:
	static void Initialize(HMODULE hModule);

	static void Debug(const char* fmt, ...);

	static void Error(const char* fmt, ...);
	static void Fatal(const char* fmt, ...);
	static void Message(const char* fmt, ...);
};