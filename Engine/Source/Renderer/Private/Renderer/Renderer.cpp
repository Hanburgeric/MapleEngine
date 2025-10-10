#include "Renderer/Renderer.h"

// STL
#include <stdexcept>
#include <string>

// Platform
#include "Platform/Window.h"

// RHI
#include "RHI/RHI.h"

// Renderer
#include "Renderer/RendererLog.h"

namespace maple::renderer {

Renderer::Renderer(platform::Window* window) {
  // Validate window pointer
  if (!window) {
    const std::string msg{ "Window pointer is null" };
    MAPLE_LOG_CRITICAL(LogRenderer, msg);
    throw std::runtime_error{ msg };
  }

  // Create the RHI backend
  MAPLE_LOG_INFO(LogRenderer, "Creating RHI...");
  rhi_ = rhi::RHI::Create(window);
  if (!rhi_) {
    const std::string msg{ "Failed to create RHI" };
    MAPLE_LOG_CRITICAL(LogRenderer, msg);
    throw std::runtime_error{ msg };
  }
  MAPLE_LOG_INFO(LogRenderer, "RHI created");
}

Renderer::~Renderer() {
  // Destroy the RHI backend
  MAPLE_LOG_INFO(LogRenderer, "Destroying RHI...");
  rhi_.reset();
  MAPLE_LOG_INFO(LogRenderer, "RHI destroyed");
}

void Renderer::BeginFrame() {
  rhi_->BeginFrame();
}

void Renderer::Clear(float r, float g, float b, float a) {
  rhi_->Clear(r, g, b, a);
}

void Renderer::EndFrame() {
  rhi_->EndFrame();
}

void Renderer::Present() {
  rhi_->Present();
}

rhi::RHI* Renderer::GetRHI() const noexcept {
  return rhi_.get();
}

} // namespace maple::renderer
