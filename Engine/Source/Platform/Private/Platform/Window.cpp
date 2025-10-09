#include "Platform/Window.h"

// STL
#include <format>
#include <stdexcept>

// SDL3
#include "SDL3/SDL.h"

// Platform
#include "Platform/PlatformLog.h"

namespace maple::platform {

Window::Window(const std::string& window_title, GraphicsAPI graphics_api)
  : platform_os_{ DetectPlatformOS() }
  , graphics_api_{ SelectGraphicsAPI(graphics_api) }
{
  // Initialize SDL3 with core subsystems
  MAPLE_LOG_DEBUG(LogPlatform, "Initializing SDL3...");
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK
                | SDL_INIT_HAPTIC | SDL_INIT_GAMEPAD)) {
    const std::string msg{ std::format("Failed to initialize SDL3: {}",
                                       SDL_GetError()) };
    MAPLE_LOG_CRITICAL(LogPlatform, msg);
    throw std::runtime_error(msg);
  }
  MAPLE_LOG_DEBUG(LogPlatform, "SDL3 successfully initialized.");

  // Configure base window flags (common to all graphics APIs)
  SDL_WindowFlags window_flags{
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_HIGH_PIXEL_DENSITY
  };

  // Add API-specific flags to enable graphics backend support
  switch (graphics_api_) {
    case GraphicsAPI::D3D12: {
      break;
    }

    case GraphicsAPI::Metal: {
      window_flags |= SDL_WINDOW_METAL;
      MAPLE_LOG_DEBUG(LogPlatform,
                      "Configured SDL3 window for use with Metal.");
      break;
    }

    case GraphicsAPI::Vulkan: {
      window_flags |= SDL_WINDOW_VULKAN;
      MAPLE_LOG_DEBUG(LogPlatform,
                      "Configured SDL3 window for use with Vulkan.");
      break;
    }

    default: { break; }
  }

  // Create the SDL window with the configured flags
  MAPLE_LOG_DEBUG(LogPlatform, "Creating SDL3 window...");
  window_.reset(SDL_CreateWindow(window_title.c_str(), 320, 200, window_flags));
  if (!window_) {
    const std::string msg{ std::format("Failed to create SDL3 window: {}",
                                       SDL_GetError()) };
    MAPLE_LOG_CRITICAL(LogPlatform, msg);

    // Clean up SDL before throwing to prevent resource leaks
    MAPLE_LOG_DEBUG(LogPlatform, "Shutting down SDL3.");
    SDL_Quit();

    throw std::runtime_error(msg);
  }
  MAPLE_LOG_DEBUG(LogPlatform, "SDL3 window successfully created.");
}

Window::~Window() {
  // Destroy the SDL3 window first
  MAPLE_LOG_DEBUG(LogPlatform, "Destroying SDL3 window...");
  window_.reset();
  MAPLE_LOG_DEBUG(LogPlatform, "SDL3 window successfully destroyed.");

  // Shut down SDL3 subsystems
  MAPLE_LOG_DEBUG(LogPlatform, "Shutting down SDL3.");
  SDL_Quit();
  MAPLE_LOG_DEBUG(LogPlatform, "SDL3 successfully shut down.");
}

bool Window::ShouldQuit() const {
  return should_quit_;
}

void Window::PollEvents() {
  // Process all pending events in the queue
  SDL_Event event{};
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_EVENT_QUIT: {
        should_quit_ = true;
        break;
      }
      default: { break; }
    }
  }
}

void* Window::GetNativeHandle() const {
  return window_.get();
}

PlatformOS Window::GetPlatformOS() const noexcept {
  return platform_os_;
}

GraphicsAPI Window::GetGraphicsAPI() const noexcept {
  return graphics_api_;
}

void Window::SDLWindowDeleter::operator()(SDL_Window* window) {
  if (window) {
    SDL_DestroyWindow(window);
  }
}

PlatformOS Window::DetectPlatformOS() const {
  // Query SDL3 for the current platform string
  const std::string detected_os{ SDL_GetPlatform() };

  // Map the string to the engine's PlatformOS enum
  if (detected_os == "Windows") {
    MAPLE_LOG_INFO(LogPlatform, "Detected platform OS: Windows");
    return PlatformOS::Windows;
  }

  if (detected_os == "macOS") {
    MAPLE_LOG_INFO(LogPlatform, "Detected platform OS: macOS");
    return PlatformOS::macOS;
  }

  if (detected_os == "Linux") {
    MAPLE_LOG_INFO(LogPlatform, "Detected platform OS: Linux");
    return PlatformOS::Linux;
  }

  if (detected_os == "iOS") {
    MAPLE_LOG_INFO(LogPlatform, "Detected platform OS: iOS");
    return PlatformOS::iOS;
  }

  if (detected_os == "Android") {
    MAPLE_LOG_INFO(LogPlatform, "Detected platform OS: Android");
    return PlatformOS::Android;
  }

  // Platform is not recognized or supported
  const std::string msg{ "Unsupported platform detected; build or run the "
                         "application on one of the following platforms: "
                         "Windows, macOS, Linux, iOS, or Android." };
  MAPLE_LOG_CRITICAL(LogPlatform, msg);
  throw std::runtime_error(msg);
}

GraphicsAPI Window::SelectGraphicsAPI(GraphicsAPI requested_api) const {
  // Check if the requested API is available on this platform
  switch (requested_api) {
    case GraphicsAPI::D3D12: {
    #ifdef MAPLE_D3D12_AVAILABLE
      MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: D3D12");
      return requested_api;
    #endif
      break;
    }

    case GraphicsAPI::Metal: {
    #ifdef MAPLE_METAL_AVAILABLE
      MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: Metal");
      return requested_api;
    #endif
      break;
    }

    case GraphicsAPI::Vulkan: {
    #ifdef MAPLE_VULKAN_AVAILABLE
      MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: Vulkan");
      return requested_api;
    #endif
      break;
    }

    default: { break; }
  }

  // Requested API is unavailable; use the platform default instead
  MAPLE_LOG_WARN(LogPlatform,
                 "Requested graphics API unavailable; "
                 "falling back to platform default.");
  return GetPlatformDefaultGraphicsAPI();
}

GraphicsAPI Window::GetPlatformDefaultGraphicsAPI() const {
  // Prefer platform-native APIs for best performance and compatibility
#ifdef MAPLE_D3D12_AVAILABLE
  MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: D3D12");
  return GraphicsAPI::D3D12;

#elif MAPLE_METAL_AVAILABLE
  MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: Metal");
  return GraphicsAPI::Metal;

  // Fall back to Vulkan as a cross-platform option
#elif MAPLE_VULKAN_AVAILABLE
  MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: Vulkan");
  return GraphicsAPI::Vulkan;

#else
  // This should never happen as CMake prevents building without a graphics API
  const std::string msg{ "No graphics API is available for selection; "
                         "consider installing the Vulkan SDK or building "
                         "the application on either Windows or macOS." };
  MAPLE_LOG_CRITICAL(LogPlatform, msg);
  throw std::runtime_error(msg);
#endif
}

} // namespace maple::platform
