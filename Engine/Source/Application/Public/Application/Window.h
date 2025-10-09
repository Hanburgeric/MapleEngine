#pragma once

// STL
#include <memory>
#include <string>

// Application
#include "Application/ApplicationAPI.h"
#include "Application/GraphicsAPI.h"

// Forward declarations
struct SDL_Window;

namespace maple::application {

/**
 * @brief SDL3-based window implementation.
 *
 * Manages window creation, event polling, and lifecycle for the application
 * using SDL3 as the underlying platform abstraction layer.
 */
class MAPLE_APPLICATION_API Window {
public:
  Window() = delete;
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(Window&&) = delete;

  /**
   * @brief Construct a window with the specified graphics API.
   *
   * Initializes SDL3, configures the window for the specified graphics API,
   * and creates the window.
   *
   * @param window_title Title displayed in the window title bar
   * @param graphics_api Graphics API backend (affects window creation flags)
   *
   * @throws std::runtime_error If SDL initialization or window creation fails
   */
  Window(const std::string& window_title, GraphicsAPI graphics_api);

  /**
   * @brief Destroy the window and shut down SDL3.
   */
  ~Window();

  /**
   * @brief Get the native SDL window handle.
   *
   * @return Platform-specific window handle as void pointer
   */
  [[nodiscard]] void* GetNativeHandle() const;

  /**
   * @brief Check if the window should close.
   *
   * @return true if a quit event has been received, false otherwise
   */
  [[nodiscard]] bool ShouldQuit() const;

  /**
   * @brief Poll and process window events.
   *
   * Processes all pending window events from SDL's event queue.
   */
  void PollEvents();

private:
  /// Custom deleter for SDL_Window unique_ptr
  struct SDLWindowDeleter {
    void operator()(SDL_Window* window);
  };

  /// Native SDL_Window handle
  std::unique_ptr<SDL_Window, SDLWindowDeleter> window_{ nullptr };

  /// Flag indicating whether a quit event has been received
  bool should_quit_{ false };
};

} // namespace maple::application
