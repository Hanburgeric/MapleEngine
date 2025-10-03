#include "Core/Platform/SDL3/SDL3Window.h"

// STL
#include <stdexcept>

// Core
#include "Core/Log.h"

namespace maple::core {
namespace platform {

SDL3Window::SDL3Window(const std::string& window_title,
                       RendererBackend renderer_backend) {
  // Initialize SDL
  MAPLE_LOG_DEBUG("Core", "Initializing SDL3...");
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    const std::string msg{ "Failed to initialize SDL3: {}", SDL_GetError() };
    MAPLE_LOG_CRITICAL("Core", msg);
    throw std::runtime_error(msg);
  }
  MAPLE_LOG_DEBUG("Core", "SDL3 successfully initialized.");

  // Configure window for use with the chosen renderer backend
  SDL_WindowFlags window_flags{
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_HIGH_PIXEL_DENSITY
  };
  switch (renderer_backend) {
    case RendererBackend::Vulkan: {
      MAPLE_LOG_DEBUG("Core", "Configured SDL3 window for use with Vulkan.");
      window_flags |= SDL_WINDOW_VULKAN;
      break;
    }
    default: { break; }
  }

  // Create window
  MAPLE_LOG_DEBUG("Core", "Creating SDL3 window...");
  window_.reset(SDL_CreateWindow(window_title.c_str(), 0, 0, window_flags));
  if (!window_) {
    const std::string msg{ "Failed to create SDL3 window: {}", SDL_GetError() };
    MAPLE_LOG_CRITICAL("Core", msg);

    // Shut down SDL before throwing
    MAPLE_LOG_DEBUG("Core", "Shutting down SDL3.");
    SDL_Quit();

    throw std::runtime_error(msg);
  }
  MAPLE_LOG_DEBUG("Core", "SDL3 window successfully created.");
}

SDL3Window::~SDL3Window() {
  // Destroy window and shut down SDL
  MAPLE_LOG_DEBUG("Core", "Destroying SDL3 window...");
  window_.reset();
  MAPLE_LOG_DEBUG("Core", "SDL3 window successfully destroyed.");

  // Shut down SDL
  MAPLE_LOG_DEBUG("Core", "Shutting down SDL3.");
  SDL_Quit();
  MAPLE_LOG_DEBUG("Core", "SDL3 successfully shut down.");
}

bool SDL3Window::ShouldQuit() const {
  return should_quit_;
}

void SDL3Window::PollEvents() {
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

} // namespace platform
} // namespace maple::core
