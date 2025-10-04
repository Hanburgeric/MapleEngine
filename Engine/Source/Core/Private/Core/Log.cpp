#include "Core/Log.h"

// spdlog
#include "spdlog/sinks/stdout_color_sinks.h"

namespace maple::core {

LogCategory::LogCategory(const std::string& name)
  : logger{ spdlog::stdout_color_mt(name) } {}

void Log::Initialize() {
  // Configure the global log level based on build configuration.
#ifdef NDEBUG
  spdlog::set_level(spdlog::level::info);
#else
  spdlog::set_level(spdlog::level::debug);
#endif
}

void Log::Shutdown() {
  // Flush all loggers and shut down background threads.
  spdlog::shutdown();
}

} // namespace maple::core
