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

/**
 * @brief Factory for creating platform-specific window implementations.
 *
 * Uses the Factory pattern to instantiate the appropriate Window
 * implementation based on the requested platform and renderer backends.
 */
class WindowFactory {
public:
  /**
   * @brief Create a platform-specific window instance.
   *
   * @param window_title Title displayed in the window title bar
   * @param platform_backend Platform abstraction layer
   * @param renderer_backend Renderer abstraction layer
   *
   * @return Unique pointer to the created Window instance
   *
   * @throws std::runtime_error If the platform backend is unsupported
   */
  static std::unique_ptr<Window> Create(const std::string& window_title,
                                        PlatformBackend platform_backend,
                                        RendererBackend renderer_backend);
};

} // namespace platform
} // namespace maple::core
