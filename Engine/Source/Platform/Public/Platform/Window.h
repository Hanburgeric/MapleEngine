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
 * @brief Cross-platform window management via SDL.
 *
 * Manages platform detection, graphics API selection with fallback support,
 * SDL lifecycle, window creation, and event handling.
 */
class MAPLE_PLATFORM_API Window {
public:
  Window() = delete;
  Window(const Window&) = delete;
  Window& operator=(const Window&) = delete;
  Window(Window&&) = delete;
  Window& operator=(Window&&) = delete;

  /**
   * @brief Construct a window with the specified title and graphics API.
   *
   * Detects the platform OS, selects an available graphics API (falling back to
   * the platform default if the requested API is unavailable), initializes SDL,
   * and creates the window for the selected API.
   *
   * @param window_title Title displayed in the window title bar
   * @param graphics_api Requested graphics API (may fall back to default)
   *
   * @throws std::runtime_error If SDL initialization or window creation fails,
   *                            or if the platform is unsupported
   */
  Window(const std::string& window_title, GraphicsAPI graphics_api);

  /**
   * @brief Destroy the window and shut down SDL.
   */
  ~Window();

  /**
   * @brief Check if the application should quit.
   *
   * @return true if a quit has been requested, false otherwise
   */
  [[nodiscard]] bool ShouldQuit() const noexcept;

  /**
   * @brief Poll and process pending window events.
   *
   * Processes all queued SDL events. Updates internal state when relevant
   * events are received (e.g., keyboard input).
   */
  void PollEvents();

  /**
   * @brief Get the platform-specific native window handle.
   *
   * @return Opaque pointer to the SDL_Window instance
   */
  [[nodiscard]] void* GetNativeHandle() const noexcept;

  /**
   * @brief Get the detected operating system platform.
   *
   * @return The platform OS detected during window construction
   */
  [[nodiscard]] PlatformOS GetPlatformOS() const noexcept;

  /**
   * @brief Get the selected graphics API.
   *
   * @return The graphics API configured for this window
   */
  [[nodiscard]] GraphicsAPI GetGraphicsAPI() const noexcept;

private:
  /**
   * @brief Custom deleter for SDL_Window unique_ptr.
   *
   * Calls SDL_DestroyWindow to properly clean up the SDL window.
   */
  struct SDLWindowDeleter {
    void operator()(SDL_Window* window);
  };

  /**
   * @brief Detect the operating system at runtime.
   *
   * Uses SDL platform detection to identify the current OS.
   *
   * @return The detected platform OS
   * @throws std::runtime_error If the platform is unsupported
   */
  [[nodiscard]] PlatformOS DetectPlatformOS() const;

  /**
   * @brief Select a graphics API based on availability.
   *
   * Validates the requested API is available on this platform and build
   * configuration. Falls back to the platform default if unavailable.
   *
   * @param requested_api The graphics API requested by the user
   * @return The selected graphics API (requested or fallback)
   */
  [[nodiscard]] GraphicsAPI SelectGraphicsAPI(GraphicsAPI requested_api) const;

  /**
   * @brief Get the default graphics API for this platform.
   *
   * Returns the preferred graphics API based on build configuration and
   * platform (D3D12 on Windows, Metal on macOS/iOS, Vulkan otherwise).
   *
   * @return The platform's default graphics API
   */
  [[nodiscard]] GraphicsAPI GetDefaultGraphicsAPI() const;

  /// SDL window instance with custom deleter
  std::unique_ptr<SDL_Window, SDLWindowDeleter> window_{ nullptr };

  /// Flag indicating whether a quit has been requested
  bool should_quit_{ false };

  /// Detected operating system platform (immutable after construction)
  const PlatformOS platform_os_;

  /// Selected graphics API for this window
  GraphicsAPI graphics_api_;
};

} // namespace maple::platform
