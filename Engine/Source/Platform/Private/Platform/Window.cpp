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
  , graphics_api_{ SelectGraphicsAPI(graphics_api) } {
  // Initialize SDL subsystems
  MAPLE_LOG_INFO(LogPlatform, "Initializing SDL3...");
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK
                | SDL_INIT_HAPTIC | SDL_INIT_GAMEPAD)) {
    const std::string msg{ std::format("Failed to initialize SDL3: {}",
                                       SDL_GetError()) };
    MAPLE_LOG_CRITICAL(LogPlatform, msg);
    throw std::runtime_error{ msg };
  }
  MAPLE_LOG_INFO(LogPlatform, "SDL3 initialized");

  // Configure base window flags
  SDL_WindowFlags window_flags{
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_HIGH_PIXEL_DENSITY
  };

  // Add flags specific to graphics APIs
  switch (graphics_api_) {
    case GraphicsAPI::D3D12: {
      break;
    }

    case GraphicsAPI::Metal: {
      window_flags |= SDL_WINDOW_METAL;
      MAPLE_LOG_INFO(LogPlatform, "Configured SDL window for use with Metal.");
      break;
    }

    case GraphicsAPI::Vulkan: {
      window_flags |= SDL_WINDOW_VULKAN;
      MAPLE_LOG_INFO(LogPlatform, "Configured SDL window for use with Vulkan.");
      break;
    }

    default: { break; }
  }

  // Create the SDL window
  MAPLE_LOG_INFO(LogPlatform, "Creating SDL window...");
  window_.reset(SDL_CreateWindow(window_title.c_str(), 320, 200, window_flags));
  if (!window_) {
    const std::string msg{ std::format("Failed to create SDL window: {}",
                                       SDL_GetError()) };
    MAPLE_LOG_CRITICAL(LogPlatform, msg);

    // Shut down SDL subsystems on failure
    MAPLE_LOG_INFO(LogPlatform, "Shutting down SDL3...");
    SDL_Quit();
    MAPLE_LOG_INFO(LogPlatform, "SDL3 shut down");

    throw std::runtime_error{ msg };
  }
  MAPLE_LOG_INFO(LogPlatform, "SDL window created");
}

Window::~Window() {
  // Destroy the SDL window
  MAPLE_LOG_INFO(LogPlatform, "Destroying SDL window...");
  window_.reset();
  MAPLE_LOG_INFO(LogPlatform, "SDL window destroyed");

  // Shut down SDL subsystems
  MAPLE_LOG_INFO(LogPlatform, "Shutting down SDL3...");
  SDL_Quit();
  MAPLE_LOG_INFO(LogPlatform, "SDL3 shut down");
}

bool Window::ShouldQuit() const noexcept {
  return should_quit_;
}

void Window::PollEvents() {
  // Poll and process all queued SDL events
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

SDL_Window* Window::GetSDLWindow() const noexcept {
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
  // Get the platform OS as a string
  const std::string detected_os{ SDL_GetPlatform() };

  // Map the string to the PlatformOS enum
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

  // Platform is not supported
  const std::string msg{ "Unsupported platform detected; build or run the "
                         "application on one of the following platforms: "
                         "Windows, macOS, Linux, iOS, or Android." };
  MAPLE_LOG_CRITICAL(LogPlatform, msg);
  throw std::runtime_error{ msg };
}

GraphicsAPI Window::SelectGraphicsAPI(GraphicsAPI requested_api) const {
  // Check if the requested API is available in this build
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
      MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: Vulkan");
      return requested_api;
    }

    default: { break; }
  }

  // Requested API unavailable, fall back to platform default
  MAPLE_LOG_WARN(LogPlatform,
                 "Requested graphics API unavailable; "
                 "falling back to platform default.");
  return GetDefaultGraphicsAPI();
}

GraphicsAPI Window::GetDefaultGraphicsAPI() const {
  // Select platform default based on build configuration
#ifdef MAPLE_D3D12_AVAILABLE
  MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: D3D12");
  return GraphicsAPI::D3D12;

#elif MAPLE_METAL_AVAILABLE
  MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: Metal");
  return GraphicsAPI::Metal;

#endif
  MAPLE_LOG_INFO(LogPlatform, "Selected graphics API: Vulkan");
  return GraphicsAPI::Vulkan;
}

} // namespace maple::platform
