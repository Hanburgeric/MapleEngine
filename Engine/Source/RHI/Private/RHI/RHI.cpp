#include "RHI/RHI.h"

// STL
#include <stdexcept>
#include <string>

// Platform
#include "Platform/GraphicsAPI.h"

// RHI
#include "Platform/Window.h"
#include "RHI/RHILog.h"
#include "Vulkan/VulkanRHI.h"

namespace maple::rhi {

std::unique_ptr<RHI> RHI::Create(platform::Window* window) {
  // Validate window pointer
  if (!window) {
    const std::string msg{ "Window pointer is null" };
    MAPLE_LOG_CRITICAL(LogRHI, msg);
    throw std::runtime_error{ msg };
  }

  // Select backend based on window's graphics API
  const platform::GraphicsAPI graphics_api{ window->GetGraphicsAPI() };
  switch (graphics_api) {
    case platform::GraphicsAPI::D3D12: {
      MAPLE_LOG_INFO(LogRHI, "Selected RHI backend: D3D12");
      // return std::make_unique<D3D12RHI>(window);
      const std::string msg{ "D3D12 RHI not yet implemented" };
      MAPLE_LOG_CRITICAL(LogRHI, msg);
      throw std::runtime_error{ msg };
    }

    case platform::GraphicsAPI::Metal: {
      MAPLE_LOG_INFO(LogRHI, "Selected RHI backend: Metal");
      // return std::make_unique<MetalRHI>(window);
      const std::string msg{ "Metal RHI not yet implemented" };
      MAPLE_LOG_CRITICAL(LogRHI, msg);
      throw std::runtime_error{ msg };
    }

    case platform::GraphicsAPI::Vulkan: {
      MAPLE_LOG_INFO(LogRHI, "Selected RHI backend: Vulkan");
      return std::make_unique<VulkanRHI>(window);
    }

    default: {
      const std::string msg{ "Unsupported RHI backend detected; choose one of "
                             "the following: D3D12, Metal, or Vulkan." };
      MAPLE_LOG_CRITICAL(LogRHI, msg);
      throw std::runtime_error{ msg };
    }
  }
}

RHI::RHI(platform::Window* window)
  : window_{ window } {}

} // namespace maple::rhi
