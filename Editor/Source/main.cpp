// Core
#include "Core/Application.h"

int main(int argc, char* argv[]) {
  maple::core::Application app{ "Maple Editor",
                                maple::core::PlatformBackend::SDL3,
                                maple::core::RendererBackend::Vulkan };
  app.Run();

  return 0;
}
