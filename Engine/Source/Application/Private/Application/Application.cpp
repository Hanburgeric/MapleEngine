#include "Application/Application.h"

// STL
#include <stdexcept>

// SDL3
#include "SDL3/SDL_platform.h"

// Application
#include "Application/ApplicationLog.h"

namespace maple::application {

Application::Application(const std::string& window_title,
                         GraphicsAPI graphics_api)
  : platform_os_{ DetectPlatformOS() }
  , graphics_api_{ SelectGraphicsAPI(graphics_api) } {
  // Initialize logging system
  core::Log::Initialize();

  // Create application window with the validated graphics API
  MAPLE_LOG_INFO(LogApplication, "Creating application window...");
  window_ = std::make_unique<Window>(window_title, graphics_api_);
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

PlatformOS Application::GetPlatformOS() const noexcept {
  return platform_os_;
}

GraphicsAPI Application::GetGraphicsAPI() const noexcept {
  return graphics_api_;
}

void Application::Run() {
  while (!window_->ShouldQuit()) {
    window_->PollEvents();
  }
}

PlatformOS Application::DetectPlatformOS() const {
  // Query SDL for the current platform and map to the PlatformOS enum
  const std::string detected_os{ SDL_GetPlatform() };
  if (detected_os == "Windows") {
    MAPLE_LOG_INFO(LogApplication, "Detected platform OS: Windows");
    return PlatformOS::Windows;
  }

  if (detected_os == "macOS") {
    MAPLE_LOG_INFO(LogApplication, "Detected platform OS: macOS");
    return PlatformOS::macOS;
  }

  if (detected_os == "Linux") {
    MAPLE_LOG_INFO(LogApplication, "Detected platform OS: Linux");
    return PlatformOS::Linux;
  }

  if (detected_os == "iOS") {
    MAPLE_LOG_INFO(LogApplication, "Detected platform OS: iOS");
    return PlatformOS::iOS;
  }

  if (detected_os == "Android") {
    MAPLE_LOG_INFO(LogApplication, "Detected platform OS: Android");
    return PlatformOS::Android;
  }

  // Unsupported platform detected
  const std::string msg{ "Unsupported platform detected; build or run the "
                         "application on one of the following platforms: "
                         "Windows, macOS, Linux, iOS, or Android." };
  MAPLE_LOG_CRITICAL(LogApplication, msg);
  throw std::runtime_error(msg);
}

GraphicsAPI Application::SelectGraphicsAPI(GraphicsAPI requested_api) const {
  // Allow user selection of a graphics API if it is available for use
  switch (requested_api) {
    case GraphicsAPI::D3D12: {
    #ifdef MAPLE_D3D12_AVAILABLE
      MAPLE_LOG_INFO(LogApplication, "Selected graphics API: D3D12");
      return requested_api;
    #endif
      break;
    }

    case GraphicsAPI::Metal: {
    #ifdef MAPLE_METAL_AVAILABLE
      MAPLE_LOG_INFO(LogApplication, "Selected graphics API: Metal");
      return requested_api;
    #endif
      break;
    }

    case GraphicsAPI::Vulkan: {
    #ifdef MAPLE_VULKAN_AVAILABLE
      MAPLE_LOG_INFO(LogApplication, "Selected graphics API: Vulkan");
      return requested_api;
    #endif
      break;
    }

    default: { break; }
  }

  // If the requested API is unavailable, fall back to the platform default
  MAPLE_LOG_WARN(LogApplication,
                 "Requested graphics API unavailable; "
                 "falling back to platform default.");
  return GetPlatformDefaultGraphicsAPI();
}

GraphicsAPI Application::GetPlatformDefaultGraphicsAPI() const {
  // Prefer platform-native graphics APIs for best performance and compatibility
#ifdef MAPLE_D3D12_AVAILABLE
  MAPLE_LOG_INFO(LogApplication, "Selected graphics API: D3D12");
  return GraphicsAPI::D3D12;

#elif MAPLE_METAL_AVAILABLE
  MAPLE_LOG_INFO(LogApplication, "Selected graphics API: Metal");
  return GraphicsAPI::Metal;

  // Fall back to Vulkan as a cross-platform option
#elif MAPLE_VULKAN_AVAILABLE
  MAPLE_LOG_INFO(LogApplication, "Selected graphics API: Vulkan");
  return GraphicsAPI::Vulkan;

#else
  // This should never happen as the build system prevents this
  const std::string msg{ "No graphics API is available for selection; "
                         "consider installing the Vulkan SDK or building"
                         "the application on either Windows or macOS." };
  MAPLE_LOG_CRITICAL(LogApplication, msg);
  throw std::runtime_error(msg);
#endif
}

} // namespace maple::application
