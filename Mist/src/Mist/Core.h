#pragma once

#ifdef MST_PLATFORM_WINDOWS
	#ifdef MST_BUILD_DLL
		#define MIST_API __declspec(dllexport)
	#else
		#define MIST_API __declspec(dllimport)
	#endif
#else
	#error Mist currently only supports Windows!
#endif

#define BIT(x) (1 << x)