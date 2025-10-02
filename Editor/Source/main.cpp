// Core
#include "Core/Application.h"

int main(int argc, char* argv[]) {
  maple::core::ApplicationProperties properties{
    "Maple Editor",
    1280, 720,
    maple::core::PlatformBackend::SDL3,
    maple::core::GraphicsAPI::Vulkan
  };

  maple::core::Application app{ properties };
  app.Run();

  return 0;
}
