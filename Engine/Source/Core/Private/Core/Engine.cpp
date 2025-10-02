#include "Core/Engine.h"

// STL
#include <iostream>

namespace maple {

Engine::Engine() {
  std::cout << "Initializing engine..." << std::endl;
}

Engine::~Engine() {
  std::cout << "Shutting down engine..." << std::endl;
}

} // namespace maple
