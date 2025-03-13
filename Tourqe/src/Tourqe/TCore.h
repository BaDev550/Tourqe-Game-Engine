#pragma once

#ifdef TU_PLATFORM_WINDOWS
	#ifdef TU_BUILD_DLL
		#define TOURQE_API __declspec(dllexport)
	#else
		#define TOURQE_API __declspec(dllimport)
	#endif // TU_BUILD_DLL
#else
	#error Tourqe Engine only supports Windows for now!
#endif // TU_PLATFORM_WINDOWS
