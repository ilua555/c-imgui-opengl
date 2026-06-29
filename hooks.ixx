module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "include/MinHook.h"
export module hooks;
import open_gl;
import open_gl_draw;
import global_modules;

export class c_hooks {
	c_hooks() = default;
	c_hooks(const c_hooks&) = delete;
	c_hooks& operator=(const c_hooks&) = delete;

public:
	static auto init() -> c_hooks* {
		static c_hooks initialization;
		return &initialization;
	}

	auto opengl_hook(HMODULE openg_gl_dll) -> bool {
		uintptr_t SwapBuffers_address = (uintptr_t)openg_gl_dll + 0x40630;
		if (MH_CreateHook((LPVOID)SwapBuffers_address, (LPVOID)&hook, (LPVOID*)&original_opengl) == MH_OK) {
			MH_EnableHook((LPVOID)SwapBuffers_address);
			return true;
		}
		return false;
	}
	
	auto open_gl_draw_hook() -> bool {
		uintptr_t glDrawElement_address = reinterpret_cast<uintptr_t>(GetProcAddress(c_module::init()->opengl(), "glDrawArrays"));
		if (MH_CreateHook((LPVOID)glDrawElement_address, (LPVOID)&glDrawHook, (LPVOID*)&glDrawOriginal) == MH_OK) {
			MH_EnableHook((LPVOID)glDrawElement_address);
			return true;
		}
		return false;
	}
};