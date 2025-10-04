#include "Application/Application.h"

// STL
#include <stdexcept>

// Application
#include "Application/ApplicationLog.h"
#include "Application/Platform/WindowFactory.h"

namespace maple::application {

Application::Application(const std::string& window_title,
                         PlatformBackend platform_backend,
                         RendererBackend renderer_backend) {
  // Initialize logging system
  core::Log::Initialize();

  // Create application window
  MAPLE_LOG_INFO(LogApplication, "Creating application window...");
  window_ = WindowFactory::Create(window_title,
                                  platform_backend,
                                  renderer_backend);
  if (!window_) {
    const std::string msg{ "Failed to create application window." };
    MAPLE_LOG_CRITICAL(LogApplication, msg);
    throw std::runtime_error(msg);
  }
  MAPLE_LOG_INFO(LogApplication, "Application window successfully created.");
}

Application::~Application() {
  // Manually destroy the application window such that
  // the logger does not shut down first
  MAPLE_LOG_INFO(LogApplication, "Destroying application window...");
  window_.reset();
  MAPLE_LOG_INFO(LogApplication, "Application window successfully destroyed.");

  // Shut down logging system
  core::Log::Shutdown();
}

void Application::Run() {
  while (!window_->ShouldQuit()) {
    window_->PollEvents();
  }
}

} // namespace maple::application
