#pragma once

// STL
#include <memory>
#include <string>

// Core
#include "Core/CoreAPI.h"
#include "Core/PlatformBackend.h"
#include "Core/RendererBackend.h"
#include "Platform/Window.h"

namespace maple::core {

class MAPLE_CORE_API Application {
public:
  Application() = delete;
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  Application(const std::string& window_title,
              PlatformBackend platform_backend,
              RendererBackend renderer_backend);

  ~Application();

  void Run();

private:
  std::unique_ptr<platform::Window> window_{ nullptr };
};

} // namespace maple::core
