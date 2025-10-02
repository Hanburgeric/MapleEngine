#include "Core/Application.h"

// STL
#include <stdexcept>

// Core
#include "Core/Platform/WindowFactory.h"

namespace maple::core {

Application::Application(const ApplicationProperties& properties) {
  window_ = platform::WindowFactory::Create(properties.window_title,
                                            properties.window_width,
                                            properties.window_height,
                                            properties.platform_backend,
                                            properties.graphics_api);
  if (!window_) {
    throw std::runtime_error("Application failed to create window");
  }
}

void Application::Run() {
  while (!window_->ShouldQuit()) {
    window_->PollEvents();

    // TODO: update & render
  }
}

} // namespace maple::core
