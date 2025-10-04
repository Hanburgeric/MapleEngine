#pragma once

/**
 * @file ApplicationAPI.h
 * @brief Dynamic library import/export macros for the Application module.
 */

#ifdef _WIN32
  #ifdef MAPLE_APPLICATION_BUILD
    #define MAPLE_APPLICATION_API __declspec(dllexport)
  #else
    #define MAPLE_APPLICATION_API __declspec(dllimport)
  #endif
#else
  #define MAPLE_APPLICATION_API
#endif
