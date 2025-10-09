#include "Application/Application.h"

// STL
#include <stdexcept>

// Application
#include "Application/ApplicationLog.h"

namespace maple::application {

Application::Application(const std::string& window_title,
                         platform::GraphicsAPI graphics_api) {
  // Initialize the logging system before any other operations
  core::Log::Initialize();

  // Create the application window with the validated graphics API
  MAPLE_LOG_INFO(LogApplication, "Creating application window...");
  window_ = std::make_unique<platform::Window>(window_title, graphics_api);
  if (!window_) {
    const std::string msg{ "Failed to create application window." };
    MAPLE_LOG_CRITICAL(LogApplication, msg);
    throw std::runtime_error(msg);
  }
  MAPLE_LOG_INFO(LogApplication, "Application window successfully created.");
}

Application::~Application() {
  // Manually destroy the application window before shutting down the logger
  MAPLE_LOG_INFO(LogApplication, "Destroying application window...");
  window_.reset();
  MAPLE_LOG_INFO(LogApplication, "Application window successfully destroyed.");

  // Shut down the logging system last
  core::Log::Shutdown();
}

void Application::Run() {
  // Run until quit is requested
  while (!window_->ShouldQuit()) {
    // Poll and process all pending window events
    window_->PollEvents();
  }
}

} // namespace maple::application
