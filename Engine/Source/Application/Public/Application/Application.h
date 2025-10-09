#pragma once

// STL
#include <memory>
#include <string>

// Application
#include "Application/ApplicationAPI.h"
#include "Application/GraphicsAPI.h"
#include "Application/PlatformOS.h"
#include "Application/Window.h"

namespace maple::application {

/**
 * @brief Core application class managing engine initialization and main loop.
 *
 * Serves as the entry point for the Maple Engine, handling initialization of
 * core systems (logging, windowing) and providing the main application loop.
 */
class MAPLE_APPLICATION_API Application {
public:
  Application() = delete;
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  /**
   * @brief Construct a new Application.
   *
   * Initializes the logging system and creates the application window with
   * the specified graphics API.
   *
   * @param window_title Title displayed in the window title bar
   * @param graphics_api Graphics API backend (e.g., Vulkan)
   *
   * @throws std::runtime_error If window creation fails
   */
  Application(const std::string& window_title, GraphicsAPI graphics_api);

  /**
   * @brief Destroy the Application.
   *
   * Shuts down the window and logging systems.
   */
  ~Application();

  /// Get the current platform operating system
  [[nodiscard]] PlatformOS GetPlatformOS() const noexcept;

  /// Get the selected graphics API backend
  [[nodiscard]] GraphicsAPI GetGraphicsAPI() const noexcept;

  /**
   * @brief Run the main application loop.
   *
   * Enters the main loop, polling for events and processing frame updates
   * until the application receives a quit signal.
   */
  void Run();

private:
  /**
   * @brief Detect the current platform operating system.
   *
   * Uses SDL_GetPlatform() to query the runtime platform and maps the result
   * to the PlatformOS enum.
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

private:
  /// Current platform operating system
  const PlatformOS platform_os_;

  /// Selected graphics API backend
  const GraphicsAPI graphics_api_;

  /// Platform-agnostic window instance
  std::unique_ptr<Window> window_{ nullptr };
};

} // namespace maple::application
