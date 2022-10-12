#pragma once

#include <memory>

#include "Core.h"
#include <spdlog\spdlog.h>

namespace Mist {

	class MIST_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
	
	// Logging Macros

	#define MST_CORE_TRACE(...) ::Mist::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define MST_CORE_INFO(...) ::Mist::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define MST_CORE_WARN(...) ::Mist::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define MST_CORE_ERROR(...) ::Mist::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define MST_CORE_FATAL(...) ::Mist::Log::GetCoreLogger()->critical(__VA_ARGS__)

	#define MST_TRACE(...) ::Mist::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define MST_INFO(...) ::Mist::Log::GetClientLogger()->info(__VA_ARGS__)
	#define MST_WARN(...) ::Mist::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define MST_ERROR(...) ::Mist::Log::GetClientLogger()->error(__VA_ARGS__)
	#define MST_FATAL(...) ::Mist::Log::GetClientLogger()->critical(__VA_ARGS__)

}
