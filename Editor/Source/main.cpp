// Application
#include "Application/Application.h"
#include "Application/GraphicsAPI.h"

int main(int argc, char* argv[]) {
  maple::application::Application app{
    "Maple Editor", maple::application::GraphicsAPI::Vulkan
  };
  app.Run();

  return 0;
}
