#include "Core/Platform/WindowFactory.h"

// STL
#include <stdexcept>

// Core
#include "Core/Platform/SDL3/SDL3Window.h"

namespace maple::core {
namespace platform {

std::unique_ptr<Window> WindowFactory::Create(const std::string& window_title,
                                              int window_width,
                                              int window_height,
                                              PlatformBackend platform_backend,
                                              GraphicsAPI graphics_api) {
  switch (platform_backend) {
    case PlatformBackend::SDL3: {
      return std::make_unique<SDL3Window>(window_title,
                                          window_width, window_height,
                                          graphics_api);
    }
    default: {
      throw std::runtime_error("Unsupported platform backend.");
    }
  }
}

} // namespace platform
} // namespace maple::core
