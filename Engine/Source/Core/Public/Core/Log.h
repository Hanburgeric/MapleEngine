#pragma once

// STL
#include <memory>
#include <string>

// spdlog
#include "spdlog/spdlog.h"

// Core
#include "CoreAPI.h"

namespace maple::core {

/**
 * @brief Logging system providing categorized output for engine modules.
 *
 * Wraps thinly around spdlog, providing a simple interface for creating and
 * managing multiple named loggers. Each module or subsystem can have
 * its own logger for fine-grained control over log output.
 *
 * Log levels are filtered at both compile-time (via SPDLOG_ACTIVE_LEVEL) and
 * runtime (via spdlog::set_level()). The compile-time level is configured in
 * CMakeLists.txt based on build configuration.
 *
 * @note This class uses the Monostate pattern - all methods are static.
 */
class MAPLE_CORE_API Log {
public:
  /**
   * @brief Initialize the logging system.
   *
   * Configures the global runtime log level based on the build configuration.
   * This only controls which logs are printed at runtime - logs below
   * the compile-time level (SPDLOG_ACTIVE_LEVEL set in CMakeLists.txt) are
   * completely removed from the binary and cannot be enabled.
   *
   * @note This must be called before any logging occurs.
   */
  static void Initialize();

  /**
   * @brief Shut down the logging system.
   *
   * Flushes all loggers and cleans up spdlog resources, including background
   * threads. This should be called before program termination to ensure proper
   * cleanup and prevent resource leaks.
   *
   * @warning No logging should occur after calling this method.
   */
  static void Shutdown();

  /**
   * @brief Get or create a logger by name.
   *
   * Retrieves an existing logger from the spdlog registry, or creates a new
   * colored console logger if one doesn't exist.
   *
   * @param name The name of the logger
   * @return Shared pointer to the requested logger
   */
  static std::shared_ptr<spdlog::logger> GetLogger(const std::string& name);
};

} // namespace maple::core

/**
 * @brief Log a trace-level message.
 *
 * Most verbose logging level for detailed execution flow.
 * Compiled out in all builds by default (requires manual SPDLOG_ACTIVE_LEVEL change).
 *
 * @param logger Logger name (e.g., "Core", "Renderer")
 * @param ... Format string and arguments (uses fmt/spdlog syntax)
 */
#define MAPLE_LOG_TRACE(logger, ...)    SPDLOG_LOGGER_TRACE(::maple::core::Log::GetLogger(logger), __VA_ARGS__)

/**
 * @brief Log a debug-level message.
 *
 * Development information for understanding application behavior.
 * Compiled in debug builds only (compiled out in release builds).
 *
 * @param logger Logger name (e.g., "Core", "Renderer")
 * @param ... Format string and arguments (uses fmt/spdlog syntax)
 */
#define MAPLE_LOG_DEBUG(logger, ...)    SPDLOG_LOGGER_DEBUG(::maple::core::Log::GetLogger(logger), __VA_ARGS__)

/**
 * @brief Log an info-level message.
 *
 * General informational messages about application lifecycle and state.
 * Compiled in all builds.
 *
 * @param logger Logger name (e.g., "Core", "Renderer")
 * @param ... Format string and arguments (uses fmt/spdlog syntax)
 */
#define MAPLE_LOG_INFO(logger, ...)     SPDLOG_LOGGER_INFO(::maple::core::Log::GetLogger(logger), __VA_ARGS__)

/**
 * @brief Log a warning-level message.
 *
 * Unexpected but recoverable conditions (e.g., fallback behavior, degraded performance).
 * Compiled in all builds.
 *
 * @param logger Logger name (e.g., "Core", "Renderer")
 * @param ... Format string and arguments (uses fmt/spdlog syntax)
 */
#define MAPLE_LOG_WARN(logger, ...)     SPDLOG_LOGGER_WARN(::maple::core::Log::GetLogger(logger), __VA_ARGS__)

/**
 * @brief Log an error-level message.
 *
 * Operation failed but application can continue (e.g., resource load failure).
 * Compiled in all builds.
 *
 * @param logger Logger name (e.g., "Core", "Renderer")
 * @param ... Format string and arguments (uses fmt/spdlog syntax)
 */
#define MAPLE_LOG_ERROR(logger, ...)    SPDLOG_LOGGER_ERROR(::maple::core::Log::GetLogger(logger), __VA_ARGS__)

/**
 * @brief Log a critical-level message.
 *
 * Catastrophic failure, application likely cannot continue (e.g., out of memory).
 * Compiled in all builds.
 *
 * @param logger Logger name (e.g., "Core", "Renderer")
 * @param ... Format string and arguments (uses fmt/spdlog syntax)
 */
#define MAPLE_LOG_CRITICAL(logger, ...) SPDLOG_LOGGER_CRITICAL(::maple::core::Log::GetLogger(logger), __VA_ARGS__)
