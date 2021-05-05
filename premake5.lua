workspace "engine"
    architecture "x64"

    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "engine"
    location "engine"
    kind "SharedLib"
    language "c++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "epch.h"
    pchsource "engine/src/epch.cpp"

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "%{prj.name}/vendor/spdlog/include",
        "%{prj.name}/src"
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "ENGINE_PLATFORM_WINDOWS",
            "ENGINE_BUILD_DLL"
        }

        postbuildcommands 
        {
            ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
        }

    filter "configurations:Debug" 
        defines "ENGINE_DEBUG"
        optimize "On"
    filter "configurations:Release" 
        defines "ENGINE_RELEASE"
        optimize "On"
    filter "configurations:Dist" 
        defines "ENGINE_Dist"
        optimize "On"
    
project "Sandbox"       
    location "engine"
    kind "ConsoleApp"
    language "c++"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "engine/vendor/spdlog/include",
        "engine/src"
    }

    links {
        "engine"
    }

    filter "system:windows"
        cppdialect "c++17"
        staticruntime "On"
        systemversion "latest"

        defines {
            "ENGINE_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug" 
        defines "ENGINE_DEBUG"
        optimize "On"
    filter "configurations:Release" 
        defines "ENGINE_RELEASE"
        optimize "On"
    filter "configurations:Dist" 
        defines "ENGINE_Dist"
        optimize "On"