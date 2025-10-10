#pragma once

// STL
#include <memory>
#include <string>

// spdlog
#include "spdlog/spdlog.h"

// Core
#include "Core/CoreExport.h"

namespace maple::core {

/**
 * @brief Global logging system initialization and shutdown.
 *
 * Static singleton interface for managing the engine's logging subsystem.
 * Provides one-time initialization and cleanup for all log categories.
 *
 * @par Compile-Time vs Runtime Filtering
 * The logging system uses two levels of filtering:
 * - Compile-time filtering (SPDLOG_ACTIVE_LEVEL) removes log calls from the
 *   binary entirely for zero overhead. Configured in CMake.
 * - Runtime filtering (spdlog::set_level, configured by Initialize()) allows
 *   dynamic log level changes but still evaluates function arguments.
 */
class MAPLE_CORE_API Log {
public:
  /**
   * @brief Initialize the logging system.
   *
   * Configures the global runtime log level based on build configuration:
   * - Debug builds: spdlog::level::debug
   * - Release builds: spdlog::level::info
   *
   * @note Must be called before any logging occurs.
   */
  static void Initialize();

  /**
   * @brief Shut down the logging system.
   *
   * Flushes all loggers and cleans up background threads. Ensures all pending
   * log messages are written before termination.
   *
   * @note Must be called before program termination to prevent resource leaks.
   *       No logging should occur after calling this method.
   */
  static void Shutdown();
};

/**
 * @brief Named logger instance for organizing log output by subsystem.
 *
 * Wraps a spdlog logger to provide categorized logging (e.g., LogApplication).
 *
 * @note Use the MAPLE_DECLARE_LOG_CATEGORY and MAPLE_DEFINE_LOG_CATEGORY macros
 *       to create categories rather than instantiating this class directly.
 */
class MAPLE_CORE_API LogCategory {
public:
  LogCategory() = delete;
  LogCategory(const LogCategory&) = delete;
  LogCategory& operator=(const LogCategory&) = delete;
  LogCategory(LogCategory&&) = delete;
  LogCategory& operator=(LogCategory&&) = delete;

  /**
   * @brief Construct a log category with the given name.
   *
   * Creates a color-enabled console logger for this category.
   *
   * @param name Category name (e.g., "LogApplication")
   *
   * @note Use the MAPLE_DEFINE_LOG_CATEGORY macro instead of calling this
   *       directly.
   */
  explicit LogCategory(const std::string& name);

  /// The underlying spdlog logger instance.
  const std::shared_ptr<spdlog::logger> logger;
};

} // namespace maple::core

/**
 * @brief Declare a log category in a header file.
 *
 * Creates an external declaration for a log category that can be used across
 * multiple translation units. Must be paired with MAPLE_DEFINE_LOG_CATEGORY
 * in exactly one .cpp file.
 *
 * @param API DLL import/export macro for the module that defines this category
 *            (e.g., MAPLE_APPLICATION_API)
 * @param CategoryName Name of the category (e.g., LogApplication)
 */
#define MAPLE_DECLARE_LOG_CATEGORY(API, CategoryName) \
        extern API maple::core::LogCategory CategoryName;

/**
 * @brief Define a log category in a source file.
 *
 * Creates the actual log category instance. Must be paired with
 * MAPLE_DECLARE_LOG_CATEGORY in a header file. This macro should appear
 * in exactly one .cpp file per category.
 *
 * @param CategoryName Name of the category (e.g., LogApplication)
 */
#define MAPLE_DEFINE_LOG_CATEGORY(CategoryName) \
        maple::core::LogCategory CategoryName{ #CategoryName };

/**
 * @brief Log a trace-level message.
 *
 * Most verbose logging level for detailed execution flow and variable values.
 * Use for fine-grained debugging information that would be too noisy in normal
 * development. Compiled out in all builds by default.
 *
 * @param Category Log category instance (e.g., LogApplication)
 * @param ... Format string and arguments (spdlog/fmt syntax)
 */
#define MAPLE_LOG_TRACE(Category, ...) \
        SPDLOG_LOGGER_TRACE(Category.logger, __VA_ARGS__)

/**
 * @brief Log a debug-level message.
 *
 * Development information for understanding application behavior and state
 * during debugging. Use for messages helpful during development but not needed
 * in release builds. Compiled in debug builds only by default.
 *
 * @param Category Log category instance (e.g., LogApplication)
 * @param ... Format string and arguments (spdlog/fmt syntax)
 */
#define MAPLE_LOG_DEBUG(Category, ...) \
        SPDLOG_LOGGER_DEBUG(Category.logger, __VA_ARGS__)

/**
 * @brief Log an info-level message.
 *
 * General informational messages about application lifecycle and state changes.
 * Use for significant events like initialization, shutdown, or major state
 * transitions. Compiled in all builds by default.
 *
 * @param Category Log category instance (e.g., LogApplication)
 * @param ... Format string and arguments (spdlog/fmt syntax)
 */
#define MAPLE_LOG_INFO(Category, ...) \
        SPDLOG_LOGGER_INFO(Category.logger, __VA_ARGS__)

/**
 * @brief Log a warning-level message.
 *
 * Unexpected but recoverable conditions that may indicate potential issues.
 * Use for situations like deprecated API usage, fallback behavior, or
 * degraded performance. Compiled in all builds by default.
 *
 * @param Category Log category instance (e.g., LogApplication)
 * @param ... Format string and arguments (spdlog/fmt syntax)
 */
#define MAPLE_LOG_WARN(Category, ...) \
        SPDLOG_LOGGER_WARN(Category.logger, __VA_ARGS__)

/**
 * @brief Log an error-level message.
 *
 * Operation failures that prevent specific functionality from working, but
 * allow the application to continue. Use for recoverable errors like resource
 * load failures or invalid user input. Compiled in all builds by default.
 *
 * @param Category Log category instance (e.g., LogApplication)
 * @param ... Format string and arguments (spdlog/fmt syntax)
 */
#define MAPLE_LOG_ERROR(Category, ...) \
        SPDLOG_LOGGER_ERROR(Category.logger, __VA_ARGS__)

/**
 * @brief Log a critical-level message.
 *
 * Catastrophic failures that prevent the application from functioning.
 * Use for unrecoverable errors like out of memory, missing required resources,
 * or corrupted critical data. Often followed by application termination.
 * Compiled in all builds by default.
 *
 * @param Category Log category instance (e.g., LogApplication)
 * @param ... Format string and arguments (spdlog/fmt syntax)
 */
#define MAPLE_LOG_CRITICAL(Category, ...) \
        SPDLOG_LOGGER_CRITICAL(Category.logger, __VA_ARGS__)
