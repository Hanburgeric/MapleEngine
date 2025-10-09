#pragma once

namespace maple::application {

/**
 * @brief Graphics API backends for the RHI.
 *
 * Defines the available graphics APIs that the Rendering Hardware Interface
 * can use. Platform availability is checked at build time and runtime.
 */
enum class GraphicsAPI {
  D3D12,
  Metal,
  Vulkan
};

} // namespace maple::application
