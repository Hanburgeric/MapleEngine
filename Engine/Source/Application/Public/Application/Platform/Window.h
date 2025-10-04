#pragma once

// STL
#include <variant>

// Application
#include "Application/ApplicationAPI.h"

// Forward declarations
struct SDL_Window;

namespace maple::application {

/// Type-safe variant for native window handles
using NativeWindowHandle = std::variant<SDL_Window*>;

/**
 * @brief Abstract interface for platform window implementations.
 *
 * Defines a platform-agnostic interface for window management.
 *
 * @note This is an abstract base class - instantiate concrete
 *       implementations via WindowFactory.
 */
class MAPLE_APPLICATION_API Window {
public:
  virtual ~Window() = default;

  /**
   * @brief Get the native window handle.
   *
   * @return Type-safe variant containing the platform-specific window handle
   *
   * @note Use std::get or std::visit to access the handle.
   */
  [[nodiscard]] virtual NativeWindowHandle GetNativeHandle() const = 0;

  /**
   * @brief Check if the window should close.
   *
   * @return true if a quit event has been received, false otherwise
   */
  [[nodiscard]] virtual bool ShouldQuit() const = 0;

  /**
   * @brief Poll and process window events.
   *
   * Processes all pending window events from the platform's event queue.
   */
  virtual void PollEvents() = 0;
};

} // namespace maple::application
