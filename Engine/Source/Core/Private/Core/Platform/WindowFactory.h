#pragma once

// STL
#include <memory>
#include <string>

// Core
#include "Core/Platform/Window.h"
#include "Core/PlatformBackend.h"
#include "Core/RendererBackend.h"

namespace maple::core {
namespace platform {

class WindowFactory {
public:
  static std::unique_ptr<Window> Create(const std::string& window_title,
                                        PlatformBackend platform_backend,
                                        RendererBackend renderer_backend);
};

} // namespace platform
} // namespace maple::core
