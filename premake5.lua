workspace "BackupEngine(2D)"
	architecture "x64"
	startproject "BackupEngine(2D)"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include Directories
IncludeDir = {}
IncludeDir["Glad"] = "Depend/Glad/include"
IncludeDir["Imgui"] = "Depend/Imgui"
IncludeDir["SFML"] = "Depend/SFML/include"
IncludeDir["SFML_Imgui"] = "Depend/Imgui-sfml"
IncludeDir["glm"] = "Depend/glm"
IncludeDir["spdlog"] = "Depend/spdlog/include"

IncludeDir["CoreStuff"] = "CoreStuff/source"
IncludeDir["MathLib"] = "MathLib/math"
IncludeDir["LowLevelStuff"] = "LowLevelStuff/source"

-- Library Directories
LibraryDir = {}
LibraryDir["SFML"] = "Depend/SFML/lib"

group "Dependencies"
	--include "Depend/GLFW"
	include "Depend/Glad"
	include "Depend/Imgui"
group ""

project "BackupEngine"
	location "BackupEngine"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/**.rc",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"CoreStuff/source",

		"%{prj.name}/src",

		"%{IncludeDir.spdlog}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.SFML_Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.CoreStuff}",
		"%{IncludeDir.MathLib}",
		"%{IncludeDir.LowLevelStuff}"
	}

	libdirs
	{
		"%{LibraryDir.SFML}"
	}

	links
	{
		"opengl32.lib",
		"openal32.lib",
		"winmm.lib",
		"gdi32.lib",
		"flac.lib",
		"vorbisenc.lib",
		"vorbis.lib",
		"vorbisfile.lib",
		"ogg.lib",
		"freetype.lib",
		"sfml-main.lib",
		"Glad",
		"Imgui",

		"user32",
		"shell32",
		"kernel32",

		"CoreStuff",
		"MathLib",
		"LowLevelStuff"
	}

	defines
	{
		"SFML_STATIC",
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"EN_PLATFORM_WINDOWS",
			"EN_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "EN_DEBUG"
		buildoptions "/MDd"
		symbols "on"
		links
		{
			"sfml-window-s-d.lib",
			"sfml-graphics-s-d.lib",
			"sfml-system-s-d.lib",
			"sfml-audio-s-d.lib",
			"sfml-network-s-d.lib"
		}

	filter "configurations:Release"
		defines "EN_RELEASE"
		buildoptions "/MD"
		optimize "on"
		links
		{
			"sfml-window-s-d.lib",
			"sfml-graphics-s-d.lib",
			"sfml-system-s-d.lib",
			"sfml-audio-s-d.lib",
			"sfml-network-s-d.lib"
		}
		
	filter "configurations:Dist"
		defines "EN_DIST"
		buildoptions "/MD"
		optimize "on"
		links
		{
			"sfml-window-s.lib",
			"sfml-graphics-s.lib",
			"sfml-system-s.lib",
			"sfml-audio-s.lib",
			"sfml-network-s.lib"
		}

project "CoreStuff"
	location "CoreStuff"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"

	defines
	{
		"SFML_STATIC"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/BackupEngine")
	}

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "pch.h"
	pchsource "CoreStuff/source/pch.cpp"

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/**.rc",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.SFML_Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.MathLib}"
	}

	libdirs
	{
		"%{LibraryDir.SFML}"
	}

	links
	{
		"opengl32.lib",
		"openal32.lib",
		"winmm.lib",
		"gdi32.lib",
		"flac.lib",
		"vorbisenc.lib",
		"vorbis.lib",
		"vorbisfile.lib",
		"ogg.lib",
		"freetype.lib",
		"sfml-main.lib",
		"Glad",
		"Imgui",

		"user32",
		"shell32",
		"kernel32"
	}

	defines
	{
		"SFML_STATIC",
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"EN_PLATFORM_WINDOWS",
			"CORESTUFF_EXPORTS"
		}

	filter "configurations:Debug"
		defines "EN_DEBUG"
		buildoptions "/MDd"
		symbols "on"
		links
		{
			"sfml-window-s-d.lib",
			"sfml-graphics-s-d.lib",
			"sfml-system-s-d.lib",
			"sfml-audio-s-d.lib",
			"sfml-network-s-d.lib"
		}

	filter "configurations:Release"
		defines "EN_RELEASE"
		buildoptions "/MD"
		optimize "on"
		links
		{
			"sfml-window-s-d.lib",
			"sfml-graphics-s-d.lib",
			"sfml-system-s-d.lib",
			"sfml-audio-s-d.lib",
			"sfml-network-s-d.lib"
		}
		
	filter "configurations:Dist"
		defines "EN_DIST"
		buildoptions "/MD"
		optimize "on"
		links
		{
			"sfml-window-s.lib",
			"sfml-graphics-s.lib",
			"sfml-system-s.lib",
			"sfml-audio-s.lib",
			"sfml-network-s.lib"
		}

project "MathLib"
	location "MathLib"
	kind "SharedLib"
	language "C++"
	cppdialect "C++20"

	defines
	{
		"SFML_STATIC"
	}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/BackupEngine")
	}

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/math/**.h",
		"%{prj.name}/math/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.glm}"
	}

	libdirs
	{
		"%{LibraryDir.SFML}"
	}

	links
	{
		"winmm.lib",
		"sfml-main.lib"
	}

	defines
	{
		"SFML_STATIC",
	}

	filter "system:windows"
		cppdialect "C++20"
		staticruntime "on"
		systemversion "latest"

		defines
		{
			"EN_PLATFORM_WINDOWS",
			"MATHLIB_EXPORTS"
		}

	filter "configurations:Debug"
		defines "EN_DEBUG"
		buildoptions "/MDd"
		symbols "on"
		links
		{
			"sfml-system-s-d.lib"
		}

	filter "configurations:Release"
		defines "EN_RELEASE"
		buildoptions "/MD"
		optimize "on"
		links
		{
			"sfml-system-s-d.lib"
		}
		
	filter "configurations:Dist"
		defines "EN_DIST"
		buildoptions "/MD"
		optimize "on"
		links
		{
			"sfml-system-s.lib"
		}

project "LowLevelStuff"
	location "LowLevelStuff"
	kind "SharedItems"
	language "C++"

	files
	{
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.hpp"
	}