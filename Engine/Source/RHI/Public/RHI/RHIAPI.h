#pragma once

/**
 * @file RHIAPI.h
 * @brief Dynamic library import/export macros for the RHI module.
 */

#ifdef _WIN32
  #ifdef MAPLE_RHI_BUILD
    #define MAPLE_RHI_API __declspec(dllexport)
  #else
    #define MAPLE_RHI_API __declspec(dllimport)
  #endif
#else
  #define MAPLE_RHI_API
#endif
