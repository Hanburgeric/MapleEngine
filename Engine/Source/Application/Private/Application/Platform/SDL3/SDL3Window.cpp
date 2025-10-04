#include "Application/Platform/SDL3/SDL3Window.h"

// STL
#include <format>
#include <stdexcept>

// Application
#include "Application/ApplicationLog.h"

namespace maple::application {

SDL3Window::SDL3Window(const std::string& window_title,
                       RendererBackend renderer_backend) {
  // Initialize SDL
  MAPLE_LOG_DEBUG(LogApplication, "Initializing SDL3...");
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    const std::string msg{ std::format("Failed to initialize SDL3: {}",
                                       SDL_GetError()) };
    MAPLE_LOG_CRITICAL(LogApplication, msg);
    throw std::runtime_error(msg);
  }
  MAPLE_LOG_DEBUG(LogApplication, "SDL3 successfully initialized.");

  // Configure window for use with the chosen renderer backend
  SDL_WindowFlags window_flags{
    SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED | SDL_WINDOW_HIGH_PIXEL_DENSITY
  };
  switch (renderer_backend) {
    case RendererBackend::Vulkan: {
      MAPLE_LOG_DEBUG(LogApplication,
                      "Configured SDL3 window for use with Vulkan.");
      window_flags |= SDL_WINDOW_VULKAN;
      break;
    }
    default: { break; }
  }

  // Create window
  MAPLE_LOG_DEBUG(LogApplication, "Creating SDL3 window...");
  window_.reset(SDL_CreateWindow(window_title.c_str(), 0, 0, window_flags));
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

SDL3Window::~SDL3Window() {
  // Destroy window and shut down SDL
  MAPLE_LOG_DEBUG(LogApplication, "Destroying SDL3 window...");
  window_.reset();
  MAPLE_LOG_DEBUG(LogApplication, "SDL3 window successfully destroyed.");

  // Shut down SDL
  MAPLE_LOG_DEBUG(LogApplication, "Shutting down SDL3.");
  SDL_Quit();
  MAPLE_LOG_DEBUG(LogApplication, "SDL3 successfully shut down.");
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

} // namespace maple::application
