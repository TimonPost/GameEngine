#include "epch.h"
#include "Log.h"

namespace Engine {
	std::shared_ptr<spdlog::logger> Log::coreLogger;
	std::shared_ptr<spdlog::logger> Log::clientLogger;

	void Log::Init()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");
		coreLogger = spdlog::stdout_color_mt("Engine");
		coreLogger->set_level(spdlog::level::trace);
		
		clientLogger = spdlog::stdout_color_mt("App");
		clientLogger->set_level(spdlog::level::trace);
	}

	Log::Log()
	{
		
	}

	Log::~Log()
	{
	}
}
