#pragma once

// STL
#include <memory>

// RHI
#include "RHI/RHIExport.h"

// Forward declarations
namespace maple::platform { class Window; }

namespace maple::rhi {

class MAPLE_RHI_API RHI {
public:
  virtual ~RHI() = default;

  RHI() = delete;
  RHI(const RHI&) = delete;
  RHI& operator=(const RHI&) = delete;
  RHI(RHI&&) = delete;
  RHI& operator=(RHI&&) = delete;

  /**
   * @brief Create an RHI backend for the window's graphics API.
   *
   * Factory function that instantiates the appropriate backend implementation
   * based on the window's configured graphics API (D3D12, Metal, or Vulkan).
   *
   * @param window Non-owning pointer to the window (must not be null)
   * @return Unique pointer to the created RHI backend
   * @throws std::runtime_error If the backend is unavailable or creation fails
   */
  static std::unique_ptr<RHI> Create(platform::Window* window);

  /**
   * @brief Begin a new rendering frame.
   */
  virtual void BeginFrame() = 0;

  /**
   * @brief Clear the screen to a solid color.
   *
   * @param r Red component [0.0 - 1.0]
   * @param g Green component [0.0 - 1.0]
   * @param b Blue component [0.0 - 1.0]
   * @param a Alpha component [0.0 - 1.0]
   */
  virtual void Clear(float r, float g, float b, float a) = 0;

  /**
   * @brief End the current rendering frame.
   */
  virtual void EndFrame() = 0;

  /**
   * @brief Present the rendered frame to the screen.
   */
  virtual void Present() = 0;

protected:
  /**
   * @brief Construct the RHI base class.
   *
   * Stores the window pointer for use by derived backend implementations.
   * Protected to enforce use of the Create() factory method.
   *
   * @param window Non-owning pointer to the window
   */
  explicit RHI(platform::Window* window);

  /// Non-owning pointer to the window
  platform::Window* window_;
};

} // namespace maple::rhi
