module;
#include "imgui/imgui.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_win32.h"

export module menu;

export class c_menu {
	c_menu() = default;
	c_menu(const c_menu&) = delete;
	c_menu& operator=(const c_menu&) = delete;

public:
	static auto init() -> c_menu* {
		static c_menu initialization;
		return &initialization;
	}

	auto menu() -> void {
		ImGui::Begin("Maestro Menu", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar);
		ImGui::Text("OOP Framework Status: 10/10");
		ImGui::End();
	}
};
