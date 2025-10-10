#pragma once

// STL
#include <memory>
#include <string>

// Platform
#include "Platform/PlatformExport.h"
#include "Platform/PlatformOS.h"
#include "Platform/GraphicsAPI.h"

// Forward declarations
struct SDL_Window;

namespace maple::platform {

/**
 * @brief SDL3-based windowing and platform abstraction.
 *
 * Manages window creation, event handling, platform detection, and graphics API
 * selection using SDL3 as the underlying platform layer.
 */
class MAPLE_PLATFORM_API Window {
public:
  Window() = delete;
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(Window&&) = delete;

  /**
   * @brief Construct a window with the specified graphics API.
   *
   * Initializes SDL3, detects the platform, validates the graphics API,
   * and creates the window configured for the selected graphics API.
   *
   * @param window_title Title displayed in the window title bar
   * @param graphics_api Graphics API backend (affects window creation flags)
   *
   * @throws std::runtime_error If SDL initialization or window creation fails
   */
  Window(const std::string& window_title, GraphicsAPI graphics_api);

  /// Destroy the window and shut down SDL3.
  ~Window();

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

  /**
   * @brief Get the native SDL window handle.
   *
   * @return Platform-specific window handle as a void pointer
   */
  [[nodiscard]] void* GetNativeHandle() const;

  /// Get the detected platform operating system
  [[nodiscard]] PlatformOS GetPlatformOS() const noexcept;

  /// Get the selected graphics API backend
  [[nodiscard]] GraphicsAPI GetGraphicsAPI() const noexcept;

private:
  /// Custom deleter for SDL_Window unique_ptr
  struct SDLWindowDeleter {
    void operator()(SDL_Window* window);
  };

  /**
   * @brief Detect the current platform operating system.
   *
   * Query the runtime platform via SDL and map the result to PlatformOS.
   *
   * @return The detected platform OS
   * @throws std::runtime_error If the platform is not recognized or supported
   */
  [[nodiscard]] PlatformOS DetectPlatformOS() const;

  /**
   * @brief Select the graphics API backend.
   *
   * Validates that the requested backend is available on the current platform.
   * If unavailable, falls back to the platform default.
   *
   * @param requested_api The graphics API requested by the user
   * @return The selected graphics API (requested or fallback)
   */
  [[nodiscard]] GraphicsAPI SelectGraphicsAPI(GraphicsAPI requested_api) const;

  /**
   * @brief Get the default graphics API for the current platform.
   *
   * Prefers platform-native backends (e.g., D3D12 on Windows, Metal on macOS)
   * for optimal performance, falling back to Vulkan as a cross-platform option.
   *
   * @return The default graphics API for this platform
   * @throws std::runtime_error If no backend is available (although the
   *                            build system should prevent this)
   */
  [[nodiscard]] GraphicsAPI GetPlatformDefaultGraphicsAPI() const;

  /// Native SDL_Window handle
  std::unique_ptr<SDL_Window, SDLWindowDeleter> window_{ nullptr };

  /// Flag indicating whether a quit event has been received
  bool should_quit_{ false };

  /// Current platform operating system
  const PlatformOS platform_os_;

  /// Selected graphics API backend
  const GraphicsAPI graphics_api_;
};

} // namespace maple::platform
