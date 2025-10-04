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
  std::unique_ptr<Window> window_{ nullptr };
};

} // namespace maple::application
