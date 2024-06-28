project "AF2D"
	kind "StaticLib"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	pchheader "afpch.h"
	pchsource "../%{prj.name}/src/afpch.cpp"

	files { "src/**.h", "src/**.cpp" }

	includedirs
	{
		"../Dependencies/glad/include",
		"../Dependencies/glm",
		"src/"
	}

	links
	{
		"glad",
		"Opengl32.lib"
	}

	targetdir ("../bin/" .. outputdir .. "-%{prj.name}")
	objdir ("../bin-int/" .. outputdir .. "-%{prj.name}")

	filter "system:windows"
		systemversion "latest"
		defines { "AF_PLATFORM_WINDOWS" }
		
	filter "system:linux"
		systemversion "latest"
		defines { "AF_PLATFORM_LINUX" }

	filter "configurations:Debug"
		defines { "AF_DEBUG" }
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines { "AF_RELEASE" }
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines { "AF_DIST" }
		runtime "Release"
		optimize "on"
