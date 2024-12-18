require "cmake"

workspace "TerminalPixel"
    configurations { "Debug", "Release" }

project "TerminalPixel"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "bin/%{cfg.buildcfg}"

    files { "src/**.hpp", "src/**.cpp" }

    includedirs { "src", "packages/glm/include/" }
    libdirs { "packages/glm/lib/" }
    links { "libglm.a" }

    filter "configurations:Debug"
        defines { "TPIXEL_DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "TPIXEL_RELEASE" }
        optimize "On"

    filter "system:linuxo"
        defines { "TPIXEL_LINUX" }
