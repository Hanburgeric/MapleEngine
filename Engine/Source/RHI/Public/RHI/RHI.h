#pragma once

// RHI
#include "RHI/RHIAPI.h"

namespace maple::rhi {

/**
 * @brief Abstract base class for Render Hardware Interface implementations.
 *
 * Defines the interface that all graphics API backends must implement.
 * Backend implementations (e.g., VulkanRHI) derive from this class and provide
 * platform-specific rendering functionality. The abstraction unifies multiple
 * graphics APIs under a common interface, enabling cross-platform rendering
 * without exposing API-specific details.
 */
class MAPLE_RHI_API RHI {
public:
  virtual ~RHI() = default;
};

} // namespace maple::rhi
