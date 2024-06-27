workspace "AF2D"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }
	startproject "Game"
	
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "AF2D"
include "Game"
