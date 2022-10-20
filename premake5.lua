workspace "Mist"
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
IncludeDir["GLFW"] = "Mist/vendor/GLFW/include"
IncludeDir["Glad"] = "Mist/vendor/Glad/include"
IncludeDir["ImGui"] = "Mist/vendor/imgui"
IncludeDir["GLM"] = "Mist/vendor/GLM/include"

include "Mist/vendor/GLFW"
include "Mist/vendor/Glad"
include "Mist/vendor/imgui"

project "Mist"
	location "Mist"
	kind "StaticLib"
	language "C++"
	staticruntime "On"
	cppdialect "C++17"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "mstpch.h"
	pchsource "Mist/src/mstpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/GLM/include/glm/**.hpp",
		"%{prj.name}/vendor/GLM/include/glm/**.inl"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.GLM}"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MST_PLATFORM_WINDOWS",
			"MST_USE_GLFW_KEYCODES",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "MST_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "MST_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "MST_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Mist/vendor/spdlog/include",
		"Mist/src",
		"%{IncludeDir.GLM}",
		"%{IncludeDir.ImGui}"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	links
	{
		"Mist"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"MST_PLATFORM_WINDOWS",
			"MST_USE_GLFW_KEYCODES"
		}

	filter "configurations:Debug"
		defines "MST_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MST_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "MST_DIST"
		optimize "On"
