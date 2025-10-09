#pragma once

namespace maple::application {

/**
 * @brief Target operating system platforms.
 *
 * Defines the operating systems that the application can run on.
 * Used for platform-specific logic and feature detection.
 */
enum class PlatformOS {
  Windows,
  macOS,
  Linux,
  iOS,
  Android
};

} // namespace maple::application
