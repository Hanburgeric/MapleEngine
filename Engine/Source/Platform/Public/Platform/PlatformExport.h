#pragma once

/**
 * @file PlatformExport.h
 * @brief Dynamic library import/export macros for the Platform module.
 */

#if defined(_WIN32) || defined(_WIN64)
  #ifdef MAPLE_PLATFORM_BUILD
    #define MAPLE_PLATFORM_API __declspec(dllexport)
  #else
    #define MAPLE_PLATFORM_API __declspec(dllimport)
  #endif
#else
  #if defined(__GNUC__) || defined(__clang__)
    #ifdef MAPLE_PLATFORM_BUILD
      #define MAPLE_PLATFORM_API __attribute__((visibility("default")))
    #else
      #define MAPLE_PLATFORM_API
    #endif
  #else
    #define MAPLE_PLATFORM_API
  #endif
#endif
