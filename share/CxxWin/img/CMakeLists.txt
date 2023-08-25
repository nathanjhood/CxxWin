cmake_minimum_required (VERSION 3.14...3.27 FATAL_ERROR)

include("CMakeRC.cmake")

project (win32res)

cmrc_add_resource_library(img
	ALIAS win32res::img
	NAMESPACE img
	ApplicationIcon.png
	Logo.png
	SmallLogo.png
	SmallLogo44x44.png
	SplashScreen.png
	StoreLogo.png
)

cmrc_add_resource_library(key
	ALIAS win32res::key
	NAMESPACE key
	Windows_TemporaryKey.pfx
)
