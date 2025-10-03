#pragma once

/**
 * @file CoreAPI.h
 * @brief Dynamic library import/export macros for the Core module.
 */

#ifdef _WIN32
  #ifdef MAPLE_CORE_BUILD
    #define MAPLE_CORE_API __declspec(dllexport)
  #else
    #define MAPLE_CORE_API __declspec(dllimport)
  #endif
#else
  #define MAPLE_CORE_API
#endif
