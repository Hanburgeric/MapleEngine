// STL
#include <iostream>

// Core
#include "Core/Engine.h"

namespace maple {

class Editor {
public:
  Editor() {
    std::cout << "Initializing editor..." << std::endl;
  }

  ~Editor() {
    std::cout << "Shutting down editor..." << std::endl;
  }

private:
  Engine engine{};
};

} // namespace maple

int main(int argc, char* argv[]) {
  maple::Editor editor{};

  return 0;
}
