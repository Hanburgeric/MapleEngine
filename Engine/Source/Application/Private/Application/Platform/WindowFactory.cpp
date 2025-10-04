#include "Application/Platform/WindowFactory.h"

// STL
#include <stdexcept>

// Application
#include "Application/ApplicationLog.h"
#include "Application/Platform/SDL3/SDL3Window.h"

namespace maple::application {

std::unique_ptr<Window> WindowFactory::Create(const std::string& window_title,
                                              PlatformBackend platform_backend,
                                              RendererBackend renderer_backend) {
  switch (platform_backend) {
    case PlatformBackend::SDL3: {
      return std::make_unique<SDL3Window>(window_title, renderer_backend);
    }
    default: {
      const std::string msg{ "Unsupported platform backend selected." };
      MAPLE_LOG_CRITICAL(LogApplication, msg);
      throw std::runtime_error(msg);
    }
  }
}

} // namespace maple::application
