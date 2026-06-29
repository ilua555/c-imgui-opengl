module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

export module global_modules;



export class c_module {
	c_module() = default;
	c_module(const c_module&) = delete;
	c_module& operator=(const c_module&) = delete;
public:
	static auto init() -> c_module* {
		static c_module initialization;
		return &initialization;
	}

	[[nodiscard]]
	auto opengl() -> HMODULE {
		return (HMODULE)GetModuleHandleA("opengl32.dll");
	}

	[[nodiscard]]
	auto user32() -> HMODULE {
		return (HMODULE)GetModuleHandleA("user32.dll");
	}

	[[nodiscard]]
	auto kernel32() -> HMODULE {
		return (HMODULE)GetModuleHandleA("kernel32.dll");
	}

};