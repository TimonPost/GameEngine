project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"
	
	targetdir ("glad/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("glad/bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"glad/include/glad/glad.h",
		"glad/include/KHR/khrplatform.h",
		"glad/src/glad.c"
	}

	includedirs {
		"glad/include"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"