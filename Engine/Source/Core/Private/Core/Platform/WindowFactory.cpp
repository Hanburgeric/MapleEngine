#include "Core/Platform/WindowFactory.h"

// STL
#include <stdexcept>

// Core
#include "Core/Log.h"
#include "Core/Platform/SDL3/SDL3Window.h"

namespace maple::core {
namespace platform {

std::unique_ptr<Window> WindowFactory::Create(const std::string& window_title,
                                              PlatformBackend platform_backend,
                                              RendererBackend renderer_backend) {
  switch (platform_backend) {
    case PlatformBackend::SDL3: {
      return std::make_unique<SDL3Window>(window_title, renderer_backend);
    }
    default: {
      const std::string msg{ "Unsupported platform backend selected." };
      MAPLE_LOG_CRITICAL("Core", msg);
      throw std::runtime_error(msg);
    }
  }
}

} // namespace platform
} // namespace maple::core
