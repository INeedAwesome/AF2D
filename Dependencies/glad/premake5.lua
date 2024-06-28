project "glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	files { "include/**.h", "src/**.c" }

	includedirs
	{
		"include/"
	}

	targetdir ("../../bin/" .. outputdir .. "-%{prj.name}")
	objdir ("../../bin-int/" .. outputdir .. "-%{prj.name}")

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
