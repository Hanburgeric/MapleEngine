#pragma once

// RHI
#include "RHI/RHI.h"

namespace maple::rhi {

/**
 * @brief Vulkan implementation of the RHI interface.
 *
 * Provides Vulkan-specific rendering functionality conforming to the
 * engine's hardware abstraction layer. This class will manage Vulkan
 * resources, command submission, and rendering operations.
 *
 * @note Implementation is currently placeholder; will be expanded as the
 *       RHI interface is defined.
 */
class VulkanRHI final : public RHI {
public:
  // Future public interface will include:
  // - Device initialization
  // - Swapchain creation
  // - Command buffer management
  // - Rendering operations

private:
  // Future private members will include:
  // - VkInstance instance_
  // - VkDevice device_
  // - VkPhysicalDevice physical_device_
  // - VkQueue graphics_queue_
  // - VkSwapchainKHR swapchain_
  // - etc.
};

} // namespace maple::rhi
