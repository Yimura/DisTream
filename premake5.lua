workspace "DisTream"
    architecture "x64"
    startproject "DisTream"

    configurations { "Debug", "Release" }

    outputdir = "%{cfg.buildcfg}"

    IncludeDir = {}
    IncludeDir["boost"] = "/usr/include/boost"
    IncludeDir["cryptlite"] = "vendor/cpp-cryptlite/include"
    IncludeDir["json"] = "vendor/json/single_include"
    IncludeDir["websocketpp"] = "/usr/include/websocketpp"

    CppVersion = "C++17"

    project "DisTream"
        location "src"
        kind "ConsoleApp"
        language "C++"

        targetdir ("bin/" .. outputdir)
        objdir ("bin/int/" .. outputdir .. "/%{prj.name}")

        PrecompiledHeaderInclude = "common.hpp"
        PrecompiledHeaderSource = "common.cpp"
        pchheader "%{PrecompiledHeaderInclude}"
        pchsource "%{PrecompiledHeaderSource}"

        files {
            "src/**.hpp",
            "src/**.cpp"
        }

        includedirs {
            "%{IncludeDir.boost}",
            "%{IncludeDir.cryptlite}",
            "%{IncludeDir.json}",
            "%{IncludeDir.websocketpp}",
            "src/"
        }

        libdirs { "bin/lib" }

        links { "crypto", "pthread", "ssl" }

        forceincludes { "%{PrecompiledHeaderInclude}" }

        flags { "NoImportLib", "Maps" }

        filter "configurations:Debug"
            flags { "LinkTimeOptimization", "MultiProcessorCompile" }
            defines { "DEBUG", "_DEBUG" }
            editandcontinue "Off"

        filter "configurations:Release"
            flags { "LinkTimeOptimization", "NoManifest", "MultiProcessorCompile" }
            defines { "RELEASE" }
            optimize "speed"
        