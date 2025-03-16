#pragma once

#include "Tourqe/TCore.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

#define TU_ENGINE_TRACE(...) ::TourqeE::Logger::GetEngineLogger()->trace(__VA_ARGS__)
#define TU_ENGINE_INFO(...) ::TourqeE::Logger::GetEngineLogger()->info(__VA_ARGS__)
#define TU_ENGINE_WARN(...) ::TourqeE::Logger::GetEngineLogger()->warn(__VA_ARGS__)
#define TU_ENGINE_ERROR(...) ::TourqeE::Logger::GetEngineLogger()->error(__VA_ARGS__)

#define TU_TRACE(...) ::TourqeE::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define TU_INFO(...) ::TourqeE::Logger::GetClientLogger()->info(__VA_ARGS__)
#define TU_WARN(...) ::TourqeE::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define TU_ERROR(...) ::TourqeE::Logger::GetClientLogger()->error(__VA_ARGS__)

namespace TourqeE {
	class TOURQE_API Logger
	{
	public:
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_EngineLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
