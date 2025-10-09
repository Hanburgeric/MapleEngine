#pragma once

namespace maple::platform {

/**
 * @brief Graphics API backends supported by the engine's RHI.
 *
 * Defines the rendering APIs available for the Render Hardware Interface.
 * Availability is determined at build time based on platform and SDK presence.
 */
enum class GraphicsAPI {
  D3D12,
  Metal,
  Vulkan
};

} // namespace maple::platform
