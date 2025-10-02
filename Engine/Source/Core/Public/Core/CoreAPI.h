#pragma once

#ifdef _WIN32
  #ifdef MAPLE_CORE_BUILD
    #define MAPLE_CORE_API __declspec(dllexport)
  #else
    #define MAPLE_CORE_API __declspec(dllimport)
  #endif
#else
  #define MAPLE_CORE_API
#endif
