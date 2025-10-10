#include "Application/Application.h"

// STL
#include <stdexcept>

// Platform
#include "Platform/Window.h"

// Renderer
#include "Renderer/Renderer.h"

// Application
#include "Application/ApplicationLog.h"

namespace maple::application {

Application::Application(const std::string& window_title,
                         platform::GraphicsAPI graphics_api) {
  // Initialize the logging system
  core::Log::Initialize();

  // Create the application window
  MAPLE_LOG_INFO(LogApplication, "Creating application window...");
  window_ = std::make_unique<platform::Window>(window_title, graphics_api);
  if (!window_) {
    const std::string msg{ "Failed to create application window" };
    MAPLE_LOG_CRITICAL(LogApplication, msg);
    throw std::runtime_error{ msg };
  }
  MAPLE_LOG_INFO(LogApplication, "Application window created");

  // Create the renderer
  MAPLE_LOG_INFO(LogApplication, "Creating renderer...");
  renderer_ = std::make_unique<renderer::Renderer>(window_.get());
  if (!renderer_) {
    const std::string msg{ "Failed to create renderer" };
    MAPLE_LOG_CRITICAL(LogApplication, msg);
    throw std::runtime_error{ msg };
  }
  MAPLE_LOG_INFO(LogApplication, "Renderer created");
}

Application::~Application() {
  // Destroy the renderer
  MAPLE_LOG_INFO(LogApplication, "Destroying renderer...");
  renderer_.reset();
  MAPLE_LOG_INFO(LogApplication, "Renderer destroyed");

  // Destroy the application window
  MAPLE_LOG_INFO(LogApplication, "Destroying application window...");
  window_.reset();
  MAPLE_LOG_INFO(LogApplication, "Application window destroyed");

  // Shut down the logging system
  core::Log::Shutdown();
}

void Application::Run() {
  while (!window_->ShouldQuit()) {
    // Process window events
    window_->PollEvents();

    // Render frame
    renderer_->BeginFrame();
    renderer_->Clear(0.0F, 0.0F, 0.0F, 1.0F);

    // ???

    // Finish and present frame
    renderer_->EndFrame();
    renderer_->Present();
  }
}

} // namespace maple::application
