#pragma once

//declspec: windows���е�

#ifdef HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API __declspec(dllexport)
	#else
		#define HAZEL_API __declspec(dllimport)
	#endif
#else
	#error Hazel only support Windows!
#endif // HZ_PLATFORM_WINDOWS


#define BIT(x) (1 << x)