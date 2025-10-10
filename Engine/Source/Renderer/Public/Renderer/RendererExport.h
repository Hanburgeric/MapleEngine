#pragma once

/**
 * @file RendererExport.h
 * @brief Dynamic library import/export macros for the Application module.
 */

#if defined(_WIN32) || defined(_WIN64)
  #ifdef MAPLE_RENDERER_BUILD
    #define MAPLE_RENDERER_API __declspec(dllexport)
  #else
    #define MAPLE_RENDERER_API __declspec(dllimport)
  #endif
#else
  #if defined(__GNUC__) || defined(__clang__)
    #ifdef MAPLE_RENDERER_BUILD
      #define MAPLE_RENDERER_API __attribute__((visibility("default")))
    #else
      #define MAPLE_RENDERER_API
    #endif
  #else
    #define MAPLE_RENDERER_API
  #endif
#endif
