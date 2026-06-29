module;
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <GL/GL.h>
#include <cstdio>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
export module open_gl;
import menu;
import settings_buttons;

//------------------------------------------------------------------------------------------------------------------
using F_opengl = __int64 (__fastcall*)(HDC hdc);
export F_opengl original_opengl = nullptr;
WNDPROC oWndProc = nullptr;
//------------------------------------------------------------------------------------------------------------------
LRESULT __stdcall My_Wnd_Proc_Hook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	if (settings::open_menu) {
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;
		switch (msg) {
			case WM_MOUSEMOVE: return true;
		}
	}


	return CallWindowProc(oWndProc, hWnd, msg, wParam, lParam);
}


export __int64 __fastcall hook(HDC hdc) {
	static bool init = false;
	if (!init){
		ImGui::CreateContext();
		ImGui_ImplWin32_Init(WindowFromDC(hdc));
		ImGui_ImplOpenGL3_Init();
		oWndProc = (WNDPROC)SetWindowLongPtrA(WindowFromDC(hdc), GWLP_WNDPROC, (LONG_PTR)My_Wnd_Proc_Hook);
		ImGui::SetNextWindowPos(ImVec2(200, 200));
		ImGui::SetNextWindowSize(ImVec2(700, 650));
		init = true;
	}

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	if (GetAsyncKeyState(VK_INSERT) & 1) {
		settings::open_menu = !settings::open_menu;
	}

	if (settings::open_menu) {
		c_menu::init()->menu();
	}
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	return original_opengl(hdc);
}

