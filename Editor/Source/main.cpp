// STL
#include <cstdlib>
#include <exception>
#include <iostream>

// Platform
#include "Platform/GraphicsAPI.h"

// Application
#include "Application/Application.h"

int main(int argc, char* argv[]) {
  try {
    // Initialize and run Maple Editor
    maple::application::Application app{ "Maple Editor",
                                         maple::platform::GraphicsAPI::Vulkan };
    app.Run();
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
