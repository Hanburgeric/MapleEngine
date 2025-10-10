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
 * @brief Log category - represents a named logger.
 *
 * Wraps a spdlog logger instance and provides a way to organize log output
 * by category (e.g., LogApplication). A category may be declared multiple
 * times, but may only be defined in a single .cpp file.
 *
 * @note Access this through the MAPLE_DECLARE_LOG_CATEGORY,
 *       MAPLE_DEFINE_LOG_CATEGORY, and MAPLE_LOG_* macros rather than directly.
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
   * Creates a color-enabled spdlog logger for the specified category.
   *
   * @param name Category name (e.g., "LogApplication")
   *
   * @note Access this through the MAPLE_DEFINE_LOG_CATEGORY macro
   *       rather than directly.
   */
  explicit LogCategory(const std::string& name);

  /**
   * @brief The underlying spdlog logger instance.
   *
   * Marked const to prevent reassignment after construction.
   *
   * @note Access this through the MAPLE_LOG_* macros rather than directly.
   */
  const std::shared_ptr<spdlog::logger> logger;
};

/**
 * @brief Logging system initialization and shutdown.
 *
 * Provides initialization and shutdown for the global logging system.
 * Log categories are declared/defined separately using macros.
 */
class MAPLE_CORE_API Log {
public:
  /**
   * @brief Initialize the logging system.
   *
   * Configures the global runtime log level based on the build configuration.
   *
   * @par Compile-Time vs. Runtime Filtering
   * Compile-time filtering (SPDLOG_ACTIVE_LEVEL) completely removes log calls
   * from the binary for zero overhead. Runtime filtering (spdlog::set_level,
   * set by this method) skips string formatting and I/O, but still evaluates
   * function arguments.
   *
   * @note This should be called before any logging occurs.
   */
  static void Initialize();

  /**
   * @brief Shut down the logging system.
   *
   * Flushes all loggers and cleans up logging resources, including background
   * threads. This should be called before program termination to ensure proper
   * cleanup and prevent resource leaks.
   *
   * @note No logging should occur after calling this method.
   */
  static void Shutdown();
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
 *            (e.g., MAPLE_APPLICATION_API, MAPLE_RENDERER_API)
 * @param CategoryName Name of the category (e.g., LogApplication, LogRenderer)
 *
 * @note The API parameter should match the module where
 *       MAPLE_DEFINE_LOG_CATEGORY is called. This ensures proper symbol
 *       import/export across DLL boundaries.
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
 * @param CategoryName Name of the category (e.g., LogApplication, LogRenderer)
 *
 * @note Defining the same category name in multiple .cpp files will cause
 *       duplicate symbol linker errors.
 */
#define MAPLE_DEFINE_LOG_CATEGORY(CategoryName) \
        maple::core::LogCategory CategoryName{ #CategoryName };

/**
 * @brief Log a trace-level message.
 *
 * Most verbose logging level for detailed execution flow.
 *
 * @param Category Log category (e.g., LogApplication, LogRenderer)
 * @param ... Format string and arguments (uses spdlog/fmt syntax)
 *
 * @note Compiled out in all builds by default.
 */
#define MAPLE_LOG_TRACE(Category, ...) \
        SPDLOG_LOGGER_TRACE(Category.logger, __VA_ARGS__)

/**
 * @brief Log a debug-level message.
 *
 * Development information for understanding application behavior.
 *
 * @param Category Log category (e.g., LogApplication, LogRenderer)
 * @param ... Format string and arguments (uses spdlog/fmt syntax)
 *
 * @note Compiled in debug builds only by default.
 */
#define MAPLE_LOG_DEBUG(Category, ...) \
        SPDLOG_LOGGER_DEBUG(Category.logger, __VA_ARGS__)

/**
 * @brief Log an info-level message.
 *
 * General informational messages about application lifecycle and state.
 *
 * @param Category Log category (e.g., LogApplication, LogRenderer)
 * @param ... Format string and arguments (uses spdlog/fmt syntax)
 *
 * @note Compiled in all builds by default.
 */
#define MAPLE_LOG_INFO(Category, ...) \
        SPDLOG_LOGGER_INFO(Category.logger, __VA_ARGS__)

/**
 * @brief Log a warning-level message.
 *
 * Unexpected but recoverable conditions (e.g., fallback behavior,
 * degraded performance).
 *
 * @param Category Log category (e.g., LogApplication, LogRenderer)
 * @param ... Format string and arguments (uses spdlog/fmt syntax)
 *
 * @note Compiled in all builds by default.
 */
#define MAPLE_LOG_WARN(Category, ...) \
        SPDLOG_LOGGER_WARN(Category.logger, __VA_ARGS__)

/**
 * @brief Log an error-level message.
 *
 * Operation failed but application can continue (e.g., resource load failure).
 *
 * @param Category Log category (e.g., LogApplication, LogRenderer)
 * @param ... Format string and arguments (uses spdlog/fmt syntax)
 *
 * @note Compiled in all builds by default.
 */
#define MAPLE_LOG_ERROR(Category, ...) \
        SPDLOG_LOGGER_ERROR(Category.logger, __VA_ARGS__)

/**
 * @brief Log a critical-level message.
 *
 * Catastrophic failure, application likely cannot continue (e.g., out of memory).
 *
 * @param Category Log category (e.g., LogApplication, LogRenderer)
 * @param ... Format string and arguments (uses spdlog/fmt syntax)
 *
 * @note Compiled in all builds by default.
 */
#define MAPLE_LOG_CRITICAL(Category, ...) \
        SPDLOG_LOGGER_CRITICAL(Category.logger, __VA_ARGS__)
