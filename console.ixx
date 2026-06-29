module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdio>
export module console;

export class c_console {
	FILE* f = nullptr;
	c_console() = default;
	c_console(const c_console&) = delete;
	c_console& operator=(const c_console&) = delete;

public:


	static auto init() -> c_console* {
		static c_console initialization;
		return &initialization;
	}

	auto open() -> void {
		if (this->f != nullptr) { return; }
		AllocConsole();
		freopen_s(&this->f, "CONIN$", "r", stdin);
		freopen_s(&this->f, "CONOUT$", "w", stdout);
	}


	auto close() -> void {
		if (this->f != nullptr) {
			HWND hConsole = GetConsoleWindow();
			FreeConsole();
			PostMessageA(hConsole, WM_CLOSE, 0, 0);
			this->f = nullptr;
		}
	}
};

