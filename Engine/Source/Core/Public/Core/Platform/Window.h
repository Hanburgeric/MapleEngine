#pragma once

// Core
#include "Core/CoreAPI.h"

namespace maple::core {
namespace platform {

/**
 * @brief Abstract interface for platform window implementations.
 *
 * Defines a platform-agnostic interface for window management.
 *
 * @note This is an abstract base class - instantiate concrete
 *       implementations via WindowFactory.
 */
class MAPLE_CORE_API Window {
public:
  virtual ~Window() = default;

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

} // namespace platform
} // namespace maple::core
