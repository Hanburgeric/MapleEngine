#pragma once

// STL
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

// Vulkan
#include "Vulkan/vulkan.hpp"

// RHI
#include "RHI/RHI.h"

// Forward declarations
namespace maple::platform{ class Window; }

namespace maple::rhi {

class VulkanRHI final : public RHI {
public:
  explicit VulkanRHI(platform::Window* window);

  ~VulkanRHI() override;

  void BeginFrame() override;
  void Clear(float r, float g, float b, float a) override;
  void EndFrame() override;
  void Present() override;

private:
  /**
   * @brief Create and initialize the Vulkan instance.
   *
   * Queries available layers and extensions, gathers required and optional
   * layers/extensions, validates their availability, and creates the Vulkan
   * instance with application information and dynamic dispatcher support.
   *
   * @throws std::runtime_error If required layers or extensions are unavailable
   */
  void CreateInstance();

  /**
   * @brief Query all available Vulkan instance layers.
   *
   * @return Set of available layer names for O(1) lookup
   */
  std::unordered_set<std::string> QueryAvailableLayers();

  /**
   * @brief Query all available Vulkan instance extensions.
   *
   * @return Set of available extension names for O(1) lookup
   */
  std::unordered_set<std::string> QueryAvailableExtensions();

  /**
   * @brief Gather required Vulkan instance layers.
   *
   * Returns layers that must be available for the instance to be created.
   * Currently empty, reserved for future use.
   *
   * @return Vector of required layer names
   */
  std::vector<std::string> GatherRequiredLayers();

  /**
   * @brief Gather required Vulkan instance extensions.
   *
   * Returns extensions that must be available, including all SDL-required
   * extensions for window surface creation.
   *
   * @return Vector of required extension names
   */
  std::vector<std::string> GatherRequiredExtensions();

  /**
   * @brief Gather optional Vulkan instance layers.
   *
   * Returns layers that are beneficial but not mandatory. Includes the
   * Khronos validation layer in debug builds.
   *
   * @return Vector of optional layer names
   */
  std::vector<std::string> GatherOptionalLayers();

  /**
   * @brief Gather optional Vulkan instance extensions.
   *
   * Returns extensions that enhance functionality but are not mandatory.
   * Includes debug utils and device address binding extensions in debug builds.
   *
   * @return Vector of optional extension names
   */
  std::vector<std::string> GatherOptionalExtensions();

  /**
   * @brief Validate that all required layers and extensions are available.
   *
   * Logs the availability status of each required layer and extension.
   *
   * @param req_layers Vector of required layer names
   * @param req_extensions Vector of required extension names
   * @param available_layers Set of available layer names
   * @param available_extensions Set of available extension names
   * @throws std::runtime_error If any required layers or extensions are missing
   */
  void ValidateRequiredLayersAndExtensions(
    const std::vector<std::string>& req_layers,
    const std::vector<std::string>& req_extensions,
    const std::unordered_set<std::string>& available_layers,
    const std::unordered_set<std::string>& available_extensions
  );

  /**
   * @brief Validate optional layers and extensions, returning available ones.
   *
   * Checks availability of optional layers and extensions, logging warnings
   * for missing ones. Updates device_address_binding_available_ if that
   * extension is available.
   *
   * @param opt_layers Vector of optional layer names
   * @param opt_extensions Vector of optional extension names
   * @param available_layers Set of available layer names
   * @param available_extensions Set of available extension names
   * @return Pair of vectors containing available layers and extensions
   */
  std::pair<std::vector<std::string>, std::vector<std::string>>
  ValidateOptionalLayersAndExtensions(
    const std::vector<std::string>& opt_layers,
    const std::vector<std::string>& opt_extensions,
    const std::unordered_set<std::string>& available_layers,
    const std::unordered_set<std::string>& available_extensions
  );

  /**
   * @brief Create the Vulkan debug messenger for validation layer output.
   *
   * Configures message severity and type filters, then creates a debug
   * messenger that routes validation messages to the logging system.
   * Only called in debug builds when validation is enabled.
   */
  void CreateDebugMessenger();

  /**
   * @brief Static callback for Vulkan validation layer messages.
   *
   * Routes validation layer messages to the appropriate logging level based
   * on severity. Called by the Vulkan debug messenger.
   *
   * @param severity Message severity level
   * @param type Message type flags
   * @param callback_data Validation message data
   * @param user_data User-defined data (unused)
   * @return VK_FALSE to continue execution
   */
  static VKAPI_ATTR vk::Bool32 VKAPI_CALL DebugCallback(
    vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
    vk::DebugUtilsMessageTypeFlagsEXT type,
    const vk::DebugUtilsMessengerCallbackDataEXT* callback_data,
    void* user_data
  );

  /// Tracks if device address binding extension is available
  bool device_address_binding_available_{ false };

  /// Vulkan instance with automatic cleanup
  vk::UniqueInstance instance_{ nullptr };

#ifdef NDEBUG
  /// Validation layers disabled in release builds
  static constexpr bool kEnableValidation{ false };
#else
  /// Validation layers enabled in debug builds
  static constexpr bool kEnableValidation{ true };
#endif

  /// Debug messenger for validation layer output (debug builds only)
  vk::UniqueDebugUtilsMessengerEXT debug_messenger_{ nullptr };
};

} // namespace maple::rhi
