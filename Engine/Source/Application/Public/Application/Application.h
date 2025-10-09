#pragma once

// STL
#include <memory>
#include <string>

// Application
#include "Application/ApplicationAPI.h"

// Platform
#include "Platform/GraphicsAPI.h"
#include "Platform/Window.h"

namespace maple::application {

/**
 * @brief Core application class managing engine initialization and main loop.
 *
 * Serves as the entry point for the Maple Engine, handling initialization of
 * core systems and providing the main application loop.
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
  Application(const std::string& window_title,
              platform::GraphicsAPI graphics_api);

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
  /// Platform-agnostic window instance
  std::unique_ptr<platform::Window> window_;
};

} // namespace maple::application
