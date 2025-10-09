#include "Application/Window.h"

// STL
#include <format>
#include <stdexcept>

// SDL3
#include "SDL3/SDL.h"

// Application
#include "Application/ApplicationLog.h"

namespace maple::application {

Window::Window(const std::string& window_title, GraphicsAPI graphics_api) {
  // Initialize SDL
  MAPLE_LOG_DEBUG(LogApplication, "Initializing SDL3...");
  if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK
                | SDL_INIT_HAPTIC | SDL_INIT_GAMEPAD)) {
    const std::string msg{ std::format("Failed to initialize SDL3: {}",
                                       SDL_GetError()) };
    MAPLE_LOG_CRITICAL(LogApplication, msg);
    throw std::runtime_error(msg);
  }
  MAPLE_LOG_DEBUG(LogApplication, "SDL3 successfully initialized.");

  // Configure window for use with the chosen graphics API
  SDL_WindowFlags window_flags{
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_HIGH_PIXEL_DENSITY
  };
  switch (graphics_api) {
    case GraphicsAPI::D3D12: { break; }

    case GraphicsAPI::Metal: {
      window_flags |= SDL_WINDOW_METAL;
      MAPLE_LOG_DEBUG(LogApplication,
                      "Configured application window for use with Metal.");
      break;
    }

    case GraphicsAPI::Vulkan: {
      window_flags |= SDL_WINDOW_VULKAN;
      MAPLE_LOG_DEBUG(LogApplication,
                      "Configured application window for use with Vulkan.");
      break;
    }

    default: { break; }
  }

  // Create window
  MAPLE_LOG_DEBUG(LogApplication, "Creating SDL3 window...");

  window_.reset(SDL_CreateWindow(window_title.c_str(), 320, 200, window_flags));
  if (!window_) {
    const std::string msg{ std::format("Failed to create SDL3 window: {}",
                                       SDL_GetError()) };
    MAPLE_LOG_CRITICAL(LogApplication, msg);

    // Shut down SDL before throwing
    MAPLE_LOG_DEBUG(LogApplication, "Shutting down SDL3.");
    SDL_Quit();

    throw std::runtime_error(msg);
  }
  MAPLE_LOG_DEBUG(LogApplication, "SDL3 window successfully created.");
}

Window::~Window() {
  // Destroy window and shut down SDL
  MAPLE_LOG_DEBUG(LogApplication, "Destroying SDL3 window...");
  window_.reset();
  MAPLE_LOG_DEBUG(LogApplication, "SDL3 window successfully destroyed.");

  // Shut down SDL
  MAPLE_LOG_DEBUG(LogApplication, "Shutting down SDL3.");
  SDL_Quit();
  MAPLE_LOG_DEBUG(LogApplication, "SDL3 successfully shut down.");
}

void* Window::GetNativeHandle() const {
  return window_.get();
}

void Window::SDLWindowDeleter::operator()(SDL_Window* window) {
  if (window) {
    SDL_DestroyWindow(window);
  }
}

bool Window::ShouldQuit() const {
  return should_quit_;
}

void Window::PollEvents() {
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

} // namespace maple::application
