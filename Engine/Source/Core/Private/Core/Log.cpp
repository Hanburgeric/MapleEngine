#include "Core/Log.h"

// spdlog
#include "spdlog/sinks/stdout_color_sinks.h"

namespace maple::core {

void Log::Initialize() {
  // Set the log verbosity depending on the build configuration
#ifdef NDEBUG
  spdlog::set_level(spdlog::level::info);
#else
  spdlog::set_level(spdlog::level::debug);
#endif
}

void Log::Shutdown() {
  spdlog::shutdown();
}

std::shared_ptr<spdlog::logger> Log::GetLogger(const std::string& name) {
  // Retrieve a logger from the registry if it exists;
  // otherwise, lazy-initialize it
  auto logger{ spdlog::get(name) };
  if (!logger) {
    logger = spdlog::stdout_color_mt(name);
  }

  return logger;
}

} // namespace maple::core
