#pragma once

// STL
#include <memory>
#include <string>

// Core
#include "Core/CoreAPI.h"
#include "Core/PlatformBackend.h"
#include "Core/GraphicsAPI.h"
#include "Platform/Window.h"

namespace maple::core {

struct ApplicationProperties {
  std::string window_title{ "Maple Application" };
  int window_width{ 1280 };
  int window_height{ 720 };
  PlatformBackend platform_backend{ PlatformBackend::SDL3 };
  GraphicsAPI graphics_api{ GraphicsAPI::Vulkan };
};

class MAPLE_CORE_API Application {
public:
  Application() = delete;
  Application(const Application&) = delete;
  Application& operator=(const Application&) = delete;
  Application(Application&&) = delete;
  Application& operator=(Application&&) = delete;

  explicit Application(const ApplicationProperties& properties);

  void Run();

private:
  std::unique_ptr<platform::Window> window_{ nullptr };
};

} // namespace maple::core
