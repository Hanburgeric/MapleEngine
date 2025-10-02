#pragma once

// STL
#include <memory>

// Core
#include "Core/Platform/Window.h"
#include "Core/PlatformBackend.h"
#include "Core/GraphicsAPI.h"

namespace maple::core {
namespace platform {

class WindowFactory {
public:
  static std::unique_ptr<Window> Create(const std::string& window_title,
                                        int window_width, int window_height,
                                        PlatformBackend platform_backend,
                                        GraphicsAPI graphics_api);
};

} // namespace platform
} // namespace maple::core
