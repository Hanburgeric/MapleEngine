#pragma once

// STL
#include <memory>
#include <string>

// Application
#include "Application/ApplicationAPI.h"
#include "Application/Platform/Window.h"
#include "Application/PlatformBackend.h"
#include "Application/RendererBackend.h"

namespace maple::application {

/**
 * @brief Core application class managing engine initialization and main loop.
 *
 * Serves as the entry point for the Maple Engine, handling initialization of
 * core systems (logging, windowing) and providing the main application loop.
 *
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
   * the specified platform and renderer backends.
   *
   * @param window_title Title displayed in the window title bar
   * @param platform_backend Platform abstraction layer (e.g., SDL3)
   * @param renderer_backend Renderer abstraction layer (e.g., Vulkan)
   *
   * @throws std::runtime_error If window creation fails
   */
  Application(const std::string& window_title,
              PlatformBackend platform_backend,
              RendererBackend renderer_backend);

  /**
   * @brief Destroy the Application.
   *
   * Shuts down the window and logging systems.
   */
  ~Application();

  /**
   * @brief Run the main application loop.
   *
   * Enters the main loop, polling for events and processing frame updates
   * until the application receives a quit signal.
   */
  void Run();

private:
  /**
   * @brief Select the renderer backend.
   *
   * Validates that the requested backend is available on the current platform.
   * If unavailable, falls back to the platform default.
   *
   * @param requested_backend The renderer backend requested by the user
   * @return The selected renderer backend (requested or fallback)
   */
  [[nodiscard]] RendererBackend SelectRendererBackend(
    RendererBackend requested_backend
  ) const;

  /**
   * @brief Get the default renderer backend for the current platform.
   *
   * Prefers platform-native backends (e.g., D3D12 on Windows, Metal on macOS)
   * for optimal performance, falling back to Vulkan as a cross-platform option.
   *
   * @return The default renderer backend for this platform
   * @throws std::runtime_error If no backend is available (although the
   *                            build system should prevent this)
   */
  [[nodiscard]] RendererBackend GetDefaultRendererBackend() const;

  /// Platform-agnostic window instance
  std::unique_ptr<Window> window_{ nullptr };
};

} // namespace maple::application
