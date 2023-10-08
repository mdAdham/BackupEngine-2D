workspace "BackupEngine(2D)"
	architecture "x86_64"
	startproject "BackupEngine-Runtime"
	--startproject "BackupEngine"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include Directories
IncludeDir = {}
IncludeDir["GLFW"] = "Depend/GLFW/include"
IncludeDir["Box2D"] = "Depend/Box2D/include"
IncludeDir["Glad"] = "Depend/Glad/include"
IncludeDir["Imgui"] = "Depend/Imgui"
IncludeDir["SFML"] = "Depend/SFML/include"
IncludeDir["SFML_Imgui"] = "Depend/Imgui-sfml"
IncludeDir["glm"] = "Depend/glm"
IncludeDir["spdlog"] = "Depend/spdlog/include"
IncludeDir["entt"] = "Depend/entt/include"
IncludeDir["yaml_cpp"] = "Depend/yaml-cpp/include"
IncludeDir["stb_image"] = "Depend/stb_image"
IncludeDir["ImGuizmo"] = "Depend/ImGuizmo"

IncludeDir["CoreStuff"] = "CoreStuff/source"
IncludeDir["MathLib"] = "MathLib/math"
IncludeDir["LowLevelStuff"] = "LowLevelStuff/source"

-- Library Directories
LibraryDir = {}
LibraryDir["SFML"] = "Depend/SFML/lib"

group "Dependencies"
	include "Depend/GLFW"
	include "Depend/yaml-cpp"
	include "Depend/Box2D"
	include "Depend/Glad"
	include "Depend/Imgui"
group ""

project "BackupEngineNut"
	location "BackupEngineNut"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Depend/spdlog/include",
		"%{wks.location}/BackupEngine/source",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.SFML_Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.ImGuizmo}"
	}

	libdirs
	{
		"%{LibraryDir.SFML}"
	}

	defines
	{
		"EN_PLATFORM_WINDOWS",
		"YAML_CPP_STATIC_DEFINE"
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

		"BackupEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "EN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EN_DIST"
		runtime "Release"
		optimize "on"
		symbols "off"

project "BackupEngine-Runtime"
	location "BackupEngine-Runtime"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "off"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	defines
	{
		"EN_PLATFORM_WINDOWS"
	}

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{wks.location}/Depend/spdlog/include",
		"%{wks.location}/BackupEngine/source",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.SFML_Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.ImGuizmo}",
		"%{IncludeDir.yaml_cpp}",
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



		"BackupEngine"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "EN_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "EN_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "EN_DIST"
		runtime "Release"
		optimize "on"
		symbols "off"

project "BackupEngine"
	location "BackupEngine"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "bcpch.h"
	pchsource "%{prj.name}/source/bcpch.cpp"

	files
	{
		"%{prj.name}/source/**.h",
		"%{prj.name}/source/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
		"Depend/ImGuizmo/ImGuizmo.h",
		"Depend/ImGuizmo/ImGuizmo.cpp",
		"%{wks.location}/Depend/Imgui-sfml/**.cpp",
		"%{wks.location}/Depend/Imgui-sfml/**.h",
	}

	includedirs
	{
		"%{prj.name}/source",
		"CoreStuff/source",

		"%{IncludeDir.GLFW}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.Box2D}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.Imgui}",
		"%{IncludeDir.SFML}",
		"%{IncludeDir.SFML_Imgui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.entt}",
		"%{IncludeDir.yaml_cpp}",
		"%{IncludeDir.stb_image}",
		"%{IncludeDir.ImGuizmo}",

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
		"GLFW",
		"Glad",
		"ImGui",
		"Box2D",
		"yaml-cpp",
		"opengl32.lib",

		"LowLevelStuff"
	}

	defines
	{
		"SFML_STATIC",
		"EN_PLATFORM_WINDOWS",
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE"
	}

	filter "files:Depend/ImGuizmo/**.cpp"
		flags { "NoPCH" }
	filter "files:LowLevelStuff/**.cpp"
		flags "NoPCH"
	filter "files:%{wks.location}/Depend/Imgui-sfml/**.cpp"
		flags "NoPCH"

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"EN_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "EN_DEBUG"
		runtime "Debug"
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
		runtime "Release"
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
		
	filter "configurations:Dist"
		defines "EN_DIST"
		runtime "Release"
		buildoptions "/MD"
		optimize "on"
		symbols "off"
		links
		{
			"sfml-window-s.lib",
			"sfml-graphics-s.lib",
			"sfml-system-s.lib",
			"sfml-audio-s.lib",
			"sfml-network-s.lib"
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