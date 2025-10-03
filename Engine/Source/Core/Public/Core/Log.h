#pragma once

// STL
#include <memory>
#include <string>

// spdlog
#include "spdlog/spdlog.h"

// Core
#include "CoreAPI.h"

namespace maple::core {

class MAPLE_CORE_API Log {
public:
  static void Initialize();
  static void Shutdown();

  static std::shared_ptr<spdlog::logger> GetLogger(const std::string& name);
};

} // namespace maple::core

#define MAPLE_LOG_TRACE(logger, ...)    SPDLOG_LOGGER_TRACE(::maple::core::Log::GetLogger(logger), __VA_ARGS__)
#define MAPLE_LOG_DEBUG(logger, ...)    SPDLOG_LOGGER_DEBUG(::maple::core::Log::GetLogger(logger), __VA_ARGS__)
#define MAPLE_LOG_INFO(logger, ...)     SPDLOG_LOGGER_INFO(::maple::core::Log::GetLogger(logger), __VA_ARGS__)
#define MAPLE_LOG_WARN(logger, ...)     SPDLOG_LOGGER_WARN(::maple::core::Log::GetLogger(logger), __VA_ARGS__)
#define MAPLE_LOG_ERROR(logger, ...)    SPDLOG_LOGGER_ERROR(::maple::core::Log::GetLogger(logger), __VA_ARGS__)
#define MAPLE_LOG_CRITICAL(logger, ...) SPDLOG_LOGGER_CRITICAL(::maple::core::Log::GetLogger(logger), __VA_ARGS__)
