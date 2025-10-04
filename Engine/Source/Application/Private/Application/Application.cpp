#include "Application/Application.h"

// STL
#include <stdexcept>

// Application
#include "Application/ApplicationLog.h"
#include "Application/Platform/WindowFactory.h"

namespace maple::application {

Application::Application(const std::string& window_title,
                         PlatformBackend platform_backend,
                         RendererBackend renderer_backend) {
  // Initialize logging system
  core::Log::Initialize();

  // Create application window with a validated renderer backend
  MAPLE_LOG_INFO(LogApplication, "Creating application window...");
  window_ = WindowFactory::Create(window_title,
                                  platform_backend,
                                  SelectRendererBackend(renderer_backend));
  if (!window_) {
    const std::string msg{ "Failed to create application window." };
    MAPLE_LOG_CRITICAL(LogApplication, msg);
    throw std::runtime_error(msg);
  }
  MAPLE_LOG_INFO(LogApplication, "Application window successfully created.");
}

Application::~Application() {
  // Manually destroy the application window such that
  // the logger does not shut down first
  MAPLE_LOG_INFO(LogApplication, "Destroying application window...");
  window_.reset();
  MAPLE_LOG_INFO(LogApplication, "Application window successfully destroyed.");

  // Shut down logging system
  core::Log::Shutdown();
}

void Application::Run() {
  while (!window_->ShouldQuit()) {
    window_->PollEvents();
  }
}

RendererBackend Application::SelectRendererBackend(
  RendererBackend requested_backend
) const {
  // Allow use of the requested backend if it is supported by the platform
  switch (requested_backend) {
    case RendererBackend::Vulkan: {
    #ifdef MAPLE_VULKAN_AVAILABLE
      MAPLE_LOG_INFO(LogApplication, "Selected Vulkan renderer backend.");
      return requested_backend;
    #endif
      break;
    }

    case RendererBackend::D3D12: {
    #ifdef MAPLE_D3D12_AVAILABLE
      MAPLE_LOG_INFO(LogApplication, "Selected D3D12 renderer backend.");
      return requested_backend;
    #endif
      break;
    }

    case RendererBackend::Metal: {
    #ifdef MAPLE_METAL_AVAILABLE
      MAPLE_LOG_INFO(LogApplication, "Selected Metal renderer backend.");
      return requested_backend;
    #endif
      break;
    }

    default: { break; }
  }

  // Otherwise, attempt to fall back to the platform default
  MAPLE_LOG_WARN(LogApplication,
                 "Requested renderer backend unavailable, "
                 "falling back to platform default");
  return GetDefaultRendererBackend();
}

RendererBackend Application::GetDefaultRendererBackend() const {
  // Prefer platform-native backends for best performance and compatibility
#ifdef MAPLE_D3D12_AVAILABLE
  MAPLE_LOG_INFO(LogApplication, "Selected D3D12 renderer backend.");
  return RendererBackend::D3D12;

#elif MAPLE_METAL_AVAILABLE
  MAPLE_LOG_INFO(LogApplication, "Selected Metal renderer backend.");
  return RendererBackend::Metal;

  // Fall back to Vulkan as a cross-platform option
#elif MAPLE_VULKAN_AVAILABLE
  MAPLE_LOG_INFO(LogApplication, "Selected Vulkan renderer backend.");
  return RendererBackend::Vulkan;

#else
  // This should never happen as the build system prevents this
  const std::string msg{ "No rendering backend is available for selection; "
                         "consider installing the Vulkan SDK or building"
                         "the application on either Windows or macOS." };
  MAPLE_LOG_CRITICAL(LogApplication, msg);
  throw std::runtime_error(msg);
#endif
}

} // namespace maple::application
