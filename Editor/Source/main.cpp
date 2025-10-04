// Application
#include "Application/Application.h"

int main(int argc, char* argv[]) {
  maple::application::Application app{
    "Maple Editor",
    maple::application::PlatformBackend::SDL3,
    maple::application::RendererBackend::Vulkan
  };
  app.Run();

  return 0;
}
