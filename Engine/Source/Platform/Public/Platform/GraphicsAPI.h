#pragma once

namespace maple::platform {

/**
 * @brief Graphics API backends supported by the engine.
 */
enum class GraphicsAPI {
  D3D12,
  Metal,
  Vulkan
};

} // namespace maple::platform
