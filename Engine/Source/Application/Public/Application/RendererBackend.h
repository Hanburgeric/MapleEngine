#pragma once

namespace maple::application {

/**
 * @brief Renderer abstraction layer backends.
 *
 * Defines the available graphics API backends for rendering
 * (e.g., Vulkan).
 *
 * @note This is part of the core module and not the renderer module
 *       as certain platform backends must know in advance
 *       which renderer backend will be used in conjunction with it.
 */
enum class RendererBackend {
  Vulkan,
  D3D12,
  Metal
};

} // namespace maple::application
