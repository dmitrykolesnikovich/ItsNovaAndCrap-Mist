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
	kind "SharedLib"
	language "C++"

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

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"IMGUI_API=__declspec(dllexport)",
			"MST_PLATFORM_WINDOWS",
			"MST_BUILD_DLL",
			"MST_USE_GLFW_KEYCODES",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS",
			"_WINDLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "MST_DEBUG"
		buildoptions "/MDd"
		symbols "On"

	filter "configurations:Release"
		defines "MST_RELEASE"
		buildoptions "/MD"
		optimize "On"

	filter "configurations:Dist"
		defines "MST_DIST"
		buildoptions "/MD"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

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

	links
	{
		"Mist"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"IMGUI_API=__declspec(dllimport)",
			"MST_PLATFORM_WINDOWS",
			"MST_USE_GLFW_KEYCODES",
			"_CRT_SECURE_NO_WARNINGS"
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
