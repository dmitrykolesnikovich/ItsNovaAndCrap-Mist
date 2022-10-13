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
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"MST_PLATFORM_WINDOWS",
			"MST_BUILD_DLL",
			"_WINDLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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
		"Mist/src"
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
			"MST_PLATFORM_WINDOWS"
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