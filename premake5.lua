workspace "ImberEngine"
	architecture "x64"
	configurations
	{
		"Debug",
		"Development",
		"Release",
	}

output_dir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

project "Engine"
	kind "ConsoleApp"
	language "C++"
	warnings "Everything"
	
	location "Engine"
	targetdir ("%{prj.location}/Binaries/" .. output_dir)
	objdir ("%{prj.location}/Intermediate/" .. output_dir)

	buildoptions
	{
		"/utf-8"
	}

	includedirs
	{
		"%{prj.location}/Source",
	}

	files
	{
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
	}
	
	filter "system:windows"
		cppdialect "C++20"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines
		{
			"IMBER_DBG"
		}
		symbols "On"

	filter "configurations:Development"
		defines
		{
			"IMBER_DEV"
		}
		symbols "On"
		optimize "On"
	
	filter "configurations:Release"
		defines
		{
			"IMBER_REL"
		}
		optimize "On"