workspace "engine"
    architecture "x64"
    startproject "Sandbox"
    configurations 
    {
        "Debug",
        "Release",
        "Dist"
    }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["glfw"] = "engine/vendor/glfw/include"
IncludeDir["glad"] = "engine/vendor/glad/include"
IncludeDir["imgui"] = "engine/vendor/imgui"
IncludeDir["glm"] = "engine/vendor/glm"
IncludeDir["stb_image"] = "engine/vendor/stb_image"

include "engine/vendor/glfw_premake5.lua"
include "engine/vendor/glad_premake5.lua"
include "engine/vendor/imgui_premake5.lua"

project "engine"
    location "engine"
    kind "StaticLib"
    language "c++"
    staticruntime "on"
    cppdialect "c++17"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "epch.h"
    pchsource "engine/src/epch.cpp"

   
    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/vendor/stb_image/**.cpp",
        "%{prj.name}/vendor/stb_image/**.h",

        "%{prj.name}/vendor/glm/glm/**.hpp",
        "%{prj.name}/vendor/glm/glm/**.inl"        
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs {
        "%{prj.name}/src",
        "%{prj.name}/vendor/spdlog/include",
        "%{IncludeDir.glfw}",
        "%{IncludeDir.glad}",
        "%{IncludeDir.imgui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}"
    }
    
    links {
        "glfw",
        "glad",
        "imgui",
        "opengl32.lib"
    }

    filter "system:windows"        
        systemversion "latest"

        defines {
            "ENGINE_PLATFORM_WINDOWS",
            "ENGINE_BUILD_DLL",
            "ENGINE_ENABLE_ASSERTS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug" 
        defines "ENGINE_DEBUG"
        runtime "Debug"
        symbols "on"
    filter "configurations:Release" 
        defines "ENGINE_RELEASE"
        optimize "on"
        runtime "Release"
    filter "configurations:Dist" 
        defines "ENGINE_Dist"
        optimize "on"
        runtime "Release"
    
project "Sandbox"       
    location "engine"
    kind "ConsoleApp"
    language "c++"
    staticruntime "on"
    cppdialect "c++17"

    targetdir("bin/" .. outputdir .. "/%{prj.name}")
    objdir("bin-int/" .. outputdir .. "/%{prj.name}")

    files {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp",
    }

    includedirs {
        "engine/vendor/spdlog/include",
        "engine/src",
        "%{IncludeDir.glm}",
    }

    links {
        "engine"
    }

    filter "system:windows"
      
        systemversion "latest"

        defines {
            "ENGINE_PLATFORM_WINDOWS",
        }

    filter "configurations:Debug" 
        defines "ENGINE_DEBUG"
        symbols "on"
        runtime "Debug"
    filter "configurations:Release" 
        defines "ENGINE_RELEASE"
        optimize "on"
        runtime "Release"
    filter "configurations:Dist" 
        defines "ENGINE_Dist"
        optimize "on"
        runtime "Release"

project "engine-editor"       
        location "engine-editor"
        kind "ConsoleApp"
        language "c++"
        staticruntime "on"
        cppdialect "c++17"
    
        targetdir("bin/" .. outputdir .. "/%{prj.name}")
        objdir("bin-int/" .. outputdir .. "/%{prj.name}")
    
        files {
            "%{prj.name}/src/**.h",
            "%{prj.name}/src/**.cpp",
        }
    
        includedirs {
            "engine/vendor/spdlog/include",
            "engine/src",
            "%{IncludeDir.glm}",
        }
    
        links {
            "engine"
        }
    
        filter "system:windows"
          
            systemversion "latest"
    
            defines {
                "ENGINE_PLATFORM_WINDOWS",
            }
    
        filter "configurations:Debug" 
            defines "ENGINE_DEBUG"
            symbols "on"
            runtime "Debug"
        filter "configurations:Release" 
            defines "ENGINE_RELEASE"
            optimize "on"
            runtime "Release"
        filter "configurations:Dist" 
            defines "ENGINE_Dist"
            optimize "on"
            runtime "Release"
                   