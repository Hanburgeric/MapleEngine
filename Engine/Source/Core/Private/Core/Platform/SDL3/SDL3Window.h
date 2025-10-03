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

/**
 * @brief SDL3-based window implementation.
 *
 * Concrete implementation of the Window interface using SDL3 for
 * cross-platform window management and event handling.
 */
class SDL3Window final : public Window {
public:
  SDL3Window() = delete;
  SDL3Window(const SDL3Window&) = delete;
  SDL3Window& operator=(const SDL3Window&) = delete;
  SDL3Window(SDL3Window&&) = delete;
  SDL3Window& operator=(SDL3Window&&) = delete;

  /**
   * @brief Construct an SDL3 window.
   *
   * Initializes SDL3, configures the window for the specified renderer
   * backend, then creates the window.
   *
   * @param window_title Title displayed in the window title bar
   * @param renderer_backend Graphics API backend (affects window flags)
   *
   * @throws std::runtime_error If SDL initialization or window creation fails
   */
  SDL3Window(const std::string& window_title, RendererBackend renderer_backend);

  /**
   * @brief Destroy the window and shut down SDL3.
   */
  ~SDL3Window() override;

  [[nodiscard]] bool ShouldQuit() const override;

  void PollEvents() override;

private:
  /**
   * @brief Custom deleter for SDL_Window unique_ptr
   */
  struct SDLWindowDeleter {
    void operator()(SDL_Window* window) {
      if (window) {
        SDL_DestroyWindow(window);
      }
    }
  };

  /// Native SDL_Window handle
  std::unique_ptr<SDL_Window, SDLWindowDeleter> window_{ nullptr };

  /// Flag indicating whether a quit event has been received
  bool should_quit_{ false };
};

} // namespace platform
} // namespace maple::core
