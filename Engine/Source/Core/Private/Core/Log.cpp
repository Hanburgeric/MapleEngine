#include "Core/Log.h"

// spdlog
#include "spdlog/sinks/stdout_color_sinks.h"

namespace maple::core {

void Log::Initialize() {
  // Configure the global runtime log level based on build configuration
#ifdef NDEBUG
  spdlog::set_level(spdlog::level::info);
#else
  spdlog::set_level(spdlog::level::debug);
#endif
}

void Log::Shutdown() {
  // Flush all loggers and clean up background threads
  spdlog::shutdown();
}

LogCategory::LogCategory(const std::string& name)
  : logger{ spdlog::stdout_color_mt(name) } {}

} // namespace maple::core
