#pragma once

// STL
#include <memory>

// Renderer
#include "Renderer/RendererExport.h"

// Forward declarations
namespace maple::platform { class Window; }
namespace maple::rhi { class RHI; }

namespace maple::renderer {

class MAPLE_RENDERER_API Renderer {
public:
  Renderer() = delete;
  Renderer(const Renderer&) = delete;
  Renderer& operator=(const Renderer&) = delete;
  Renderer(Renderer&&) = delete;
  Renderer& operator=(Renderer&&) = delete;

  explicit Renderer(platform::Window* window);

  ~Renderer();

  /**
   * @brief Begin a new rendering frame.
   */
  void BeginFrame();

  /**
   * @brief Clear the screen to a solid color.
   *
   * @param r Red component [0.0 - 1.0]
   * @param g Green component [0.0 - 1.0]
   * @param b Blue component [0.0 - 1.0]
   * @param a Alpha component [0.0 - 1.0]
   */
  void Clear(float r, float g, float b, float a);

  /**
   * @brief End the current rendering frame.
   */
  void EndFrame();

  /**
   * @brief Present the rendered frame to the screen.
   */
  void Present();

  /**
   * @brief Get direct access to the RHI backend.
   *
   * Provides raw access to the underlying graphics API abstraction for
   * advanced use cases requiring low-level control.
   *
   * @return Non-owning pointer to the RHI backend
   */
  [[nodiscard]] rhi::RHI* GetRHI() const noexcept;

private:
  /// Abstracted graphics API backend
  std::unique_ptr<rhi::RHI> rhi_{ nullptr };
};

} // namespace maple::renderer
