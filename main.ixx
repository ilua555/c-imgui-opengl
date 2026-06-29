module;
#define WIN32_LEAN_AND_MEAN
#define CONSOLE_DEBUG (1) //поставить 0 если не нужна консоль и отладка
#include <windows.h>
#include <cstdio>
#include <cstdlib>
#include "include/MinHook.h"
export module main;
import console;
import open_gl;
import global_modules;
import hooks;

DWORD WINAPI core(LPVOID lpParam) {

#if CONSOLE_DEBUG == 1
	c_console::init()->open();
#endif

	MH_STATUS minhook = MH_Initialize();
	if (minhook != MH_OK) { return 0; }
	//-----------------------------------------------------------------
	HMODULE open_gl_dll = c_module::init()->opengl();
	if (!c_hooks::init()->opengl_hook(open_gl_dll)) {
	#if CONSOLE_DEBUG == 1
		printf("\nopengl_hook dont power!!!");
	#endif
	}
	//------------------------------------------------------------------
	if (!c_hooks::init()->open_gl_draw_hook()) {
	#if CONSOLE_DEBUG == 1
		printf("\nopengl_draw_hook dont power!!!");
	#endif
	}
	while (true) { Sleep(10); }

	return 1;
}


export class c_main {
	HMODULE m_hmodule = nullptr;
	c_main(HMODULE hModule) : m_hmodule(hModule) {};
	c_main(const c_main&) = delete;
	c_main& operator=(const c_main&) = delete;
public:
	static auto init(HMODULE hModule = nullptr) -> c_main* {
		static c_main initialization(hModule);
		return &initialization;
	}

	auto StartThread() -> void {
		char k[] = {'k','e','r','n','e','l','3','2','.', 'd', 'l', 'l', '\0'};
		char t[] = { 'C','r','e','a','t','e','T','h','r','e' , 'a', 'd', '\0' };
		auto pCT = (decltype(&CreateThread))GetProcAddress(GetModuleHandleA(k), t);
		if (pCT == nullptr) [[unlikely]] { MessageBoxA(nullptr, "error_pct", "error", MB_OK); return; }
		(*pCT)(nullptr, 0, &core, this->m_hmodule, 0, 0);
	}
};