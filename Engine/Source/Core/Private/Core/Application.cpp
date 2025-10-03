#include "Core/Application.h"

// STL
#include <stdexcept>

// Core
#include "Core/Log.h"
#include "Core/Platform/WindowFactory.h"

namespace maple::core {

Application::Application(const std::string& window_title,
                         PlatformBackend platform_backend,
                         RendererBackend renderer_backend) {
  // Initialize logging system
  Log::Initialize();

  // Create application window
  MAPLE_LOG_INFO("Core", "Creating application window...");
  window_ = platform::WindowFactory::Create(window_title,
                                            platform_backend,
                                            renderer_backend);
  if (!window_) {
    const std::string msg{ "Failed to create application window." };
    MAPLE_LOG_CRITICAL("Core", msg);
    throw std::runtime_error(msg);
  }
  MAPLE_LOG_INFO("Core", "Application window successfully created.");
}

Application::~Application() {
  // Manually destroy the application window such that
  // the logger does not shut down first
  MAPLE_LOG_INFO("Core", "Destroying application window...");
  window_.reset();
  MAPLE_LOG_INFO("Core", "Application window successfully destroyed.");

  // Shut down logging system
  Log::Shutdown();
}

void Application::Run() {
  while (!window_->ShouldQuit()) {
    window_->PollEvents();

    // TODO: update & render
  }
}

} // namespace maple::core
