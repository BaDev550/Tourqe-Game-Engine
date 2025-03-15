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

#ifdef TU_DEBUG
	#define TU_ENABLE_ASSERTS
#endif
#ifdef TU_ENABLE_ASSERTS
	#define TU_ASSERT(x, ...) {if(!(x)) { TU_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define TU_ENGINE_ASSERT(x, ...) {if(!(x)) { TU_ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define TU_ASSERT(x, ...)
	#define TU_ENGINE_ASSERT(x, ...)
#endif // TU_ENABLE_ASSERTS

#define BIT(x) (x << x)
#define TU_BIND_EVENT_FUNCTION(fn) std::bind(&fn, this, std::placeholders::_1)