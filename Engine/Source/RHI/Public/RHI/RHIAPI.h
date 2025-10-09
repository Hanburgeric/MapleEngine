#pragma once

/**
 * @file RHIAPI.h
 * @brief Dynamic library import/export macros for the RHI module.
 */

#if defined(_WIN32) || defined(_WIN64)
  #ifdef MAPLE_RHI_BUILD
    #define MAPLE_RHI_API __declspec(dllexport)
  #else
    #define MAPLE_RHI_API __declspec(dllimport)
  #endif
#else
  #if defined(__GNUC__) || defined(__clang__)
    #ifdef MAPLE_RHI_BUILD
      #define MAPLE_RHI_API __attribute__((visibility("default")))
    #else
      #define MAPLE_RHI_API
    #endif
  #else
    #define MAPLE_RHI_API
  #endif
#endif
