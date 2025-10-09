#pragma once

// RHI
#include "RHI/RHIAPI.h"

namespace maple::rhi {

/**
 * @brief Abstract base class for Render Hardware Interface implementations.
 *
 * Defines the interface that all graphics API backends must implement.
 * Backend implementations (VulkanRHI, D3D12RHI, MetalRHI) derive from
 * this class and provide platform-specific rendering functionality.
 *
 * The RHI abstraction allows the engine to support multiple graphics APIs
 * with a unified interface, enabling cross-platform rendering without
 * exposing API-specific details to higher-level engine code.
 *
 * @note This is a foundational interface that will be expanded with methods
 *       for device initialization, resource management, command submission,
 *       and rendering operations.
 */
class MAPLE_RHI_API RHI {
public:
  /// Virtual destructor for proper cleanup of derived classes
  virtual ~RHI() = default;

  // Future interface methods will include:
  // - virtual void Initialize() = 0;
  // - virtual void BeginFrame() = 0;
  // - virtual void EndFrame() = 0;
  // - virtual void CreateBuffer(...) = 0;
  // - virtual void CreateTexture(...) = 0;
  // - virtual void SubmitCommands(...) = 0;
  // - etc.
};

} // namespace maple::rhi
