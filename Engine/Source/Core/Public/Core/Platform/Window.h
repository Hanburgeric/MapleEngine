#pragma once

// Core
#include "Core/CoreAPI.h"

namespace maple::core {
namespace platform {

class MAPLE_CORE_API Window {
public:
  virtual ~Window() = default;

  [[nodiscard]] virtual bool ShouldQuit() const = 0;
  virtual void PollEvents() = 0;
};

} // namespace platform
} // namespace maple::core
