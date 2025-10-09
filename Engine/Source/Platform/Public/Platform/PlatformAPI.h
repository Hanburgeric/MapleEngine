#pragma once

/**
 * @file PlatformAPI.h
 * @brief Dynamic library import/export macros for the Platform module.
 */

#ifdef _WIN32
  #ifdef MAPLE_PLATFORM_BUILD
    #define MAPLE_PLATFORM_API __declspec(dllexport)
  #else
    #define MAPLE_PLATFORM_API __declspec(dllimport)
  #endif
#else
  #define MAPLE_PLATFORM_API
#endif
