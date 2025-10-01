// STL
#include <iostream>

// Maple
#include "Engine.h"

int main(int argc, char* argv[]) {
  std::cout << "Initializing editor..." << std::endl;

  {
    maple::Engine engine{};
  }

  std::cout << "Shutting down editor..." << std::endl;
}
