project "imgui"
	kind "StaticLib"
	language "C++"
	staticruntime "on"
	cppdialect "C++17"

	targetdir ("imgui/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("imgui/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"imgui/imconfig.h",
		"imgui/imgui.h",
		"imgui/imgui.cpp",
		"imgui/imgui_draw.cpp",
		"imgui/imgui_internal.h",
		"imgui/imgui_widgets.cpp",
		"imgui/imstb_rectpack.h",
		"imgui/imstb_textedit.h",
		"imgui/imstb_truetype.h",
		"imgui/imgui_demo.cpp"
	}

	filter "system:windows"
		systemversion "latest"

	filter "system:linux"
		pic "On"
		systemversion "latest"
	

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"