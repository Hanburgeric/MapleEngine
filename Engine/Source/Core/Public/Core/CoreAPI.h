#pragma once

/**
 * @file CoreAPI.h
 * @brief Dynamic library import/export macros for the Core module.
 */

#if defined(_WIN32) || defined(_WIN64)
  #ifdef MAPLE_CORE_BUILD
    #define MAPLE_CORE_API __declspec(dllexport)
  #else
    #define MAPLE_CORE_API __declspec(dllimport)
  #endif
#else
  #if defined(__GNUC__) || defined(__clang__)
    #ifdef MAPLE_CORE_BUILD
      #define MAPLE_CORE_API __attribute__((visibility("default")))
    #else
      #define MAPLE_CORE_API
    #endif
  #else
    #define MAPLE_CORE_API
  #endif
#endif
