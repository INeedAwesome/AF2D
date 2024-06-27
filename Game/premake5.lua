project "Game"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++20"
	staticruntime "on"

	files { "src/**.h", "src/**.cpp" }

	includedirs
	{
		"../AF2D/src/",
		"src/"
	}

	links { "AF2D" }

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
		symbols "On"

	filter "configurations:Release"
		defines { "AF_RELEASE" }
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		kind "WindowedApp"
		defines { "AF_DIST" }
		runtime "Release"
		optimize "on"
