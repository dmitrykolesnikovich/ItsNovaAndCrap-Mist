#pragma once

#ifdef MST_PLATFORM_WINDOWS
	#ifdef MST_DYNAMIC_LINK
		#ifdef MST_BUILD_DLL
			#define MIST_API __declspec(dllexport)
		#else
			#define MIST_API __declspec(dllimport)
		#endif
	#else
		#define MIST_API 
	#endif
#else
	#error Mist currently only supports Windows!
#endif

#ifdef MST_DEBUG
	#define MST_ENABLE_ASSERTS
#endif

#ifdef MST_ENABLE_ASSERTS
	#define MST_ASSERT(x, ...) { if (!(x)) { MST_ERROR("Mist Error: {0} (MST_ASSERT)", __VA_ARGS__); __debugbreak(); } }
	#define MST_CORE_ASSERT(x, ...) { if (!(x)) { MST_CORE_ERROR("Mist Error: {0} (MST_CORE_ASSERT)", __VA_ARGS__); __debugbreak(); } }
#else
	#define MST_ASSERT(x, ...) 
	#define MST_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define MST_BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)
