#include "Core/Platform/SDL3/SDL3Window.h"

// STL
#include <stdexcept>

namespace maple::core {
namespace platform {

SDL3Window::SDL3Window(const std::string& window_title,
                       int window_width, int window_height,
                       GraphicsAPI graphics_api) {
  // Initialize SDL
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    throw std::runtime_error(SDL_GetError());
  }

  // Configure window flags according to the graphics API
  SDL_WindowFlags window_flags{ SDL_WINDOW_RESIZABLE
                                | SDL_WINDOW_HIGH_PIXEL_DENSITY };
  switch (graphics_api) {
    case GraphicsAPI::Vulkan: {
      window_flags |= SDL_WINDOW_VULKAN;
      break;
    }
    default: { break; }
  }

  // Create window
  window_.reset(SDL_CreateWindow(window_title.c_str(),
                                 window_width, window_height,
                                 window_flags));
  if (!window_) {
    SDL_Quit();
    throw std::runtime_error(SDL_GetError());
  }
}

SDL3Window::~SDL3Window() {
  // Destroy window
  window_.reset();

  // Shut down SDL
  SDL_Quit();
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
