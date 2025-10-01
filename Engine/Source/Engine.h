#pragma once

#ifdef _WIN32
  #ifdef ENGINE_BUILD
    #define MAPLE_API __declspec(dllexport)
  #else
    #define MAPLE_API __declspec(dllimport)
  #endif
#else
  #define MAPLE_API __attribute__((visibility("default")))
#endif

namespace maple {

class MAPLE_API Engine {
public:
  Engine();
  ~Engine();
};

} // namespace maple
