#pragma once

// STL
#include <memory>
#include <string>

// Platform
#include "Platform/GraphicsAPI.h"

// Application
#include "Application/ApplicationExport.h"

// Forward declarations
namespace maple::platform{ class Window; }
namespace maple::renderer{ class Renderer; }

namespace maple::application {

/**
 * @brief Core application class managing the engine's main loop and subsystems.
 *
 * Serves as the composition root and entry point for the engine. Manages
 * initialization and shutdown of core subsystems (e.g. logging), provides the
 * main application loop, and manages  layers for extending engine functionality.
 */
class MAPLE_APPLICATION_API Application {
public:
  Application() = delete;
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  /**
   * @brief Construct an application with the specified window and graphics API.
   *
   * Initializes all engine subsystems and prepares the application for execution.
   *
   * @param window_title Title displayed in the window title bar
   * @param graphics_api Requested graphics API (may fall back to default)
   *
   * @throws std::runtime_error If critical subsystem initialization fails
   */
  Application(const std::string& window_title,
              platform::GraphicsAPI graphics_api);

  /**
   * @brief Shut down all subsystems and destroy the application.
   */
  ~Application();

  /**
   * @brief Run the main application loop.
   *
   * Executes the engine's frame loop, updating and rendering all active
   * subsystems and layers until termination is requested.
   */
  void Run();

private:
  /// Application window
  std::unique_ptr<platform::Window> window_{ nullptr };

  /// High-level rendering system
  std::unique_ptr<renderer::Renderer> renderer_{ nullptr };
};

} // namespace maple::application
