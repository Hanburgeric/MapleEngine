#pragma once

// RHI
#include "RHI/RHI.h"

// Forward declarations
namespace maple::platform{ class Window; }

namespace maple::rhi {

class VulkanRHI final : public RHI {
public:
  explicit VulkanRHI(platform::Window* window);

  ~VulkanRHI() override;

  void BeginFrame() override;
  void Clear(float r, float g, float b, float a) override;
  void EndFrame() override;
  void Present() override;

private:

};

} // namespace maple::rhi
