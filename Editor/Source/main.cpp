// Platform
#include "Platform/GraphicsAPI.h"

// Application
#include "Application/Application.h"

int main(int argc, char* argv[]) {
  // Initialize and run Maple Editor
  maple::application::Application app{ "Maple Editor",
                                       maple::platform::GraphicsAPI::Vulkan };
  app.Run();

  return 0;
}
