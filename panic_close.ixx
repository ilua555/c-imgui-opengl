module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "include/MinHook.h"

export module panic_close;
import console;

export class c_close {
	c_close() = default;
	c_close(const c_close&) = delete;
	c_close& operator=(const c_close&) = delete;
public:
	static auto init() -> c_close* {
		static c_close initialization;
		return &initialization;
	}

	auto close(HMODULE hModule) -> void {
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
		c_console::init()->close();
		FreeLibraryAndExitThread(hModule, 1);
	}

	auto close_for_detach(HMODULE hModule) -> void {
		MH_DisableHook(MH_ALL_HOOKS);
		MH_Uninitialize();
	}
};