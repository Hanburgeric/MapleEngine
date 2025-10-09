#pragma once

namespace maple::platform {

/**
 * @brief Operating system platforms supported by the engine.
 *
 * Represents the target platform detected at runtime via SDL3.
 * Used for platform-specific code paths and graphics API selection.
 */
enum class PlatformOS {
  Windows,
  macOS,
  Linux,
  iOS,
  Android
};

} // namespace maple::platform
