#pragma once

// STL
#include <memory>
#include <string>

// SDL3
#include "SDL3/SDL.h"

// Core
#include "Core/Platform/Window.h"
#include "Core/RendererBackend.h"

namespace maple::core {
namespace platform {

class SDL3Window final : public Window {
public:
  SDL3Window() = delete;
  SDL3Window(const SDL3Window&) = delete;
  SDL3Window& operator=(const SDL3Window&) = delete;
  SDL3Window(SDL3Window&&) = delete;
  SDL3Window& operator=(SDL3Window&&) = delete;

  SDL3Window(const std::string& window_title, RendererBackend renderer_backend);
  ~SDL3Window() override;

  [[nodiscard]] bool ShouldQuit() const override;
  void PollEvents() override;

private:
  struct SDLWindowDeleter {
    void operator()(SDL_Window* window) {
      if (window) {
        SDL_DestroyWindow(window);
      }
    }
  };

  std::unique_ptr<SDL_Window, SDLWindowDeleter> window_{ nullptr };
  bool should_quit_{ false };
};

} // namespace platform
} // namespace maple::core
