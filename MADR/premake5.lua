-- premake5.lua
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "ProjectMegaton"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Distribute"
    }

    startproject "ProjectMegaton"

IncludeDir = {}

IncludeDir["GLFW"] = "MADRengine/_thirdparty/includes/GLFW"
IncludeDir["Glad"] = "MADRengine/_thirdparty/includes/glad"
IncludeDir["ImGui"] = "MADRengine/_thirdparty/includes/imgui-master"
IncludeDir["glm"] = "MADRengine/_thirdparty/includes/glm"
IncludeDir["nlohmann"] = "MADRengine/_thirdparty/includes/nlohmann"
IncludeDir["magicenum"] = "MADRengine/_thirdparty/includes/magic_enum/include"
IncludeDir["fmod"] = "MADRengine/_thirdparty/includes/fmod/inc"
IncludeDir["freetype"] = "MADRengine/_thirdparty/includes/freetype/inc"
IncludeDir["rttr"] = "MADRengine/_thirdparty/includes/RTTR/include"
IncludeDir["stbi"] = "MADRengine/_thirdparty/includes/stbi/inc"
IncludeDir["boost"] = "MADRengine/_thirdparty/includes/Boost/inc"
IncludeDir["SDL"] = "MADRengine/_thirdparty/includes/SDL2"
IncludeDir["KHR"] = "MADRengine/_thirdparty/includes/KHR"

group "Dependencies"
--[[
    include "MADRengine/_thirdparty/GLFW"
    include "MADRengine/_thirdparty/Glad"
    include "MADRengine/_thirdparty/imgui"
    ]]
group ""

project "MADRengine"
    location "MADRengine"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("_bin/" .. outputdir .. "/%{prj.name}")
    objdir ("_bin-int/" .. outputdir .. "/%{prj.name}")

    --pchheader "MADRpch.h"
    --pchsource "MADRengine/src/MADRpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp",
        "%{prj.name}/src/**.c"
    }
    
    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    includedirs
    {
        "%{prj.name}/src",
        "%{prj.name}/_thirdparty/includes/spdlog/include",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.nlohmann}",
        "%{IncludeDir.magicenum}",
        "%{IncludeDir.freetype}",
        "%{IncludeDir.rttr}",
        "%{IncludeDir.stbi}",
        "%{IncludeDir.boost}",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.KHR}"
    }

    links
    {
        "glfw3_mt.lib",
        "SDL2.lib",
        "SDL2main.lib"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "MADR_PLATFORM_WINDOWS",
            "GLFW_INCLUDE_NONE"
        }

    filter "configurations:Debug"
        defines
        {
            "MADR_ENABLE_ASSERTS",
            "MADR_DEBUG",
            "_DEBUG",
            "_CONSOLE"
        }

        links
        {
            --"MADRengine/_thirdparty/fmod/lib/x64/fmodL_vc.lib",
            --"MADRengine/_thirdparty/freetype/lib/freetype_debug.lib",
            --"MADRengine/_thirdparty/RTTR/lib/debug/librttr_core_d.lib"
        }
        runtime "Debug"
        symbols "on"
        

    filter "configurations:Release"
        defines
        {
            "MADR_ENABLE_ASSERTS",
            "MADR_RELEASE",
            "NDEBUG",
            "_CONSOLE"
        }

        links
        {
            --"MADRengine/_thirdparty/fmod/lib/x64/fmod_vc.lib",
            --"MADRengine/_thirdparty/freetype/lib/freetype.lib",
            --"MADRengine/_thirdparty/RTTR/lib/relwithdebug/librttr_core.lib"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }

    filter "configurations:Distribute"
        defines
        {
            "MADR_DIST",
            "NDEBUG"
        }

        links
        {
            --"MADRengine/_thirdparty/fmod/lib/x64/fmod_vc.lib",
            --"MADRengine/_thirdparty/freetype/lib/freetype.lib",
            --"MADRengine/_thirdparty/RTTR/lib/release/librttr_core.lib"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }

project "ProjectMegaton"
    location "ProjectMegaton"
    kind "ConsoleApp"
    staticruntime "off"

    language "C++"
    cppdialect "C++17"

    debugdir ("_bin/" .. outputdir .. "/%{prj.name}")
    targetdir ("_bin/" .. outputdir .. "/%{prj.name}")
    objdir ("_bin-int/" .. outputdir .. "/%{prj.name}")

    pchheader "pmpch.h"
    pchsource "ProjectMegaton/src/pmpch.cpp"

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.hpp",
        "%{prj.name}/src/**.cpp"
    }

    includedirs
    {
        "%{prj.name}/src",
        "MADRengine/src",
        "MADRengine/_thirdparty/spdlog/include",
        "MADRengine/_thirdparty/",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.json}",
        "%{IncludeDir.magicenum}",
        "%{IncludeDir.freetype}",
        "%{IncludeDir.rttr}",
		    "%{IncludeDir.stbi}",
        "%{IncludeDir.SDL}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.KHR}"
        
    }

    links
    {
        "MADRengine"
    }

    flags
    {
        "MultiProcessorCompile"
    }

    linkoptions { "/IGNORE:4204,4099" }

    postbuildcommands
    {
        --"robocopy \"../assets\" \"../_bin/" .. outputdir .. "/%{prj.name}/assets\" /mir"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "MADR_PLATFORM_WINDOWS"
        }

    filter "configurations:Debug"
        postbuildcommands
        {
            --"robocopy \"../MADRengine/_thirdparty/fmod/lib/x64/\" \"../_bin/" .. outputdir .. "/%{prj.name}\" fmodL.dll"
        }

        defines
        {
            "MADR_DEBUG",
            "_DEBUG",
            "_CONSOLE"
        }
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        postbuildcommands
        {
            --"robocopy \"../MADRengine/_thirdparty/fmod/lib/x64/\" \"../_bin/" .. outputdir .. "/%{prj.name}\" fmod.dll"
        }

        defines
        {
            "MADR_RELEASE",
            "NDEBUG",
            "_CONSOLE"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }

    filter "configurations:Distribute"
        postbuildcommands
        {
            --"robocopy \"../MADRengine/_thirdparty/fmod/lib/x64/\" \"../_bin/" .. outputdir .. "/%{prj.name}\" fmod.dll"
        }

        defines
        {
            "MADR_DIST",
            "NDEBUG"
        }
        runtime "Release"
        optimize "speed"

        buildoptions
        {
            "/Ot"
        }