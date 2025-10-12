#include "RHI/Vulkan/VulkanRHI.h"

// STL
#include <cstdint>
#include <format>
#include <stdexcept>

// SDL3
#include "SDL3/SDL_vulkan.h"

// Vulkan
VULKAN_HPP_DEFAULT_DISPATCH_LOADER_DYNAMIC_STORAGE

// Platform
#include "Platform/Window.h"

// RHI
#include "RHI/RHILog.h"

namespace maple::rhi {
VulkanRHI::VulkanRHI(platform::Window* window)
  : RHI{ window } {
  // Initialize the default dynamic dispatcher with global functions
  VULKAN_HPP_DEFAULT_DISPATCHER.init(vkGetInstanceProcAddr);

  // Create Vulkan instance with required layers and extensions
  CreateInstance();

  // Setup debug messenger for validation layer output
  if constexpr (kEnableValidation) {
    CreateDebugMessenger();
  }
}

VulkanRHI::~VulkanRHI() {
  // ???
}

void VulkanRHI::BeginFrame() {
  // ???
}

void VulkanRHI::Clear(float r, float g, float b, float a) {
  // ???
}

void VulkanRHI::EndFrame() {
  // ???
}

void VulkanRHI::Present() {
  // ???
}

void VulkanRHI::CreateInstance() {
  MAPLE_LOG_INFO(LogRHI, "Creating Vulkan instance...");

  // Query available layers and extensions
  const auto available_layers{ QueryAvailableLayers() };
  const auto available_extensions{ QueryAvailableExtensions() };

  // Gather required layers and extensions
  const auto req_layers{ GatherRequiredLayers() };
  const auto req_extensions{ GatherRequiredExtensions() };

  // Validate required layers and extensions (throws if missing)
  ValidateRequiredLayersAndExtensions(req_layers, req_extensions,
                                      available_layers, available_extensions);

  // Gather optional layers and extensions
  const auto opt_layers{ GatherOptionalLayers() };
  const auto opt_extensions{ GatherOptionalExtensions() };

  // Validate optional layers and extensions; returns available
  // layers and extensions, warns otherwise
  auto [available_opt_layers, available_opt_extensions] {
    ValidateOptionalLayersAndExtensions(opt_layers, opt_extensions,
                                        available_layers, available_extensions)
  };

  // Combine required and available optional layers for instance creation
  std::vector<const char*> enabled_layers{};
  for (const auto& layer : req_layers) {
    enabled_layers.emplace_back(layer.c_str());
  }
  for (const auto& layer : available_opt_layers) {
    enabled_layers.emplace_back(layer.c_str());
  }

  // Combine required and available optional extensions for instance creation
  std::vector<const char*> enabled_extensions{};
  for (const auto& extension : req_extensions) {
    enabled_extensions.emplace_back(extension.c_str());
  }
  for (const auto& extension : available_opt_extensions) {
    enabled_extensions.emplace_back(extension.c_str());
  }

  // Configure application and engine information
  constexpr vk::ApplicationInfo app_info{
    .pApplicationName = "Maple Application",
    .applicationVersion = VK_MAKE_VERSION(0, 1, 0),
    .pEngineName = "Maple Engine",
    .engineVersion = VK_MAKE_VERSION(0, 1, 0),
    .apiVersion = vk::ApiVersion12
  };

  // Configure instance creation with validated layers and extensions
  const vk::InstanceCreateInfo create_info{
    .pApplicationInfo = &app_info,
    .enabledLayerCount = static_cast<std::uint32_t>(enabled_layers.size()),
    .ppEnabledLayerNames = enabled_layers.data(),
    .enabledExtensionCount = static_cast<std::uint32_t>(enabled_extensions.size()),
    .ppEnabledExtensionNames = enabled_extensions.data()
  };

  // Create the Vulkan instance
  instance_ = vk::createInstanceUnique(create_info);

  // Initialize the default dynamic dispatcher with instance-level functions
  VULKAN_HPP_DEFAULT_DISPATCHER.init(*instance_);

  MAPLE_LOG_INFO(LogRHI, "Vulkan instance created");
}

std::unordered_set<std::string> VulkanRHI::QueryAvailableLayers() {
  std::unordered_set<std::string> layer_names{};

  // Query all available Vulkan layers and extract their names
  const auto layers{ vk::enumerateInstanceLayerProperties() };
  for (const auto& layer : layers) {
    layer_names.emplace(layer.layerName.data());
  }

  return layer_names;
}

std::unordered_set<std::string> VulkanRHI::QueryAvailableExtensions() {
  std::unordered_set<std::string> extension_names{};

  // Query all available Vulkan instance extensions and extract their names
  const auto extensions{ vk::enumerateInstanceExtensionProperties() };
  for (const auto& extension : extensions) {
    extension_names.emplace(extension.extensionName.data());
  }

  return extension_names;
}

std::vector<std::string> VulkanRHI::GatherRequiredLayers() {
  std::vector<std::string> layer_names{};
  return layer_names;
}

std::vector<std::string> VulkanRHI::GatherRequiredExtensions() {
  std::vector<std::string> extension_names{};

  // Get required extensions from SDL
  std::uint32_t num_sdl_extensions{};
  const char* const* sdl_extensions{
    SDL_Vulkan_GetInstanceExtensions(&num_sdl_extensions)
  };

  // Add SDL extensions to the list
  for (std::uint32_t i{ 0U }; i < num_sdl_extensions; ++i) {
    extension_names.emplace_back(sdl_extensions[i]);
  }

  return extension_names;
}

std::vector<std::string> VulkanRHI::GatherOptionalLayers() {
  std::vector<std::string> layer_names{};

  // Add validation layer in debug builds for error checking
  if constexpr (kEnableValidation) {
    layer_names.emplace_back("VK_LAYER_KHRONOS_validation");
  }

  return layer_names;
}

std::vector<std::string> VulkanRHI::GatherOptionalExtensions() {
  std::vector<std::string> extension_names{};

  // Add debug and validation extensions in debug builds
  if constexpr (kEnableValidation) {
    // Debug utils extension for validation layer messages
    extension_names.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

    // Device address binding report extension
    extension_names.emplace_back(
      VK_EXT_DEVICE_ADDRESS_BINDING_REPORT_EXTENSION_NAME
    );
  }

  return extension_names;
}

void VulkanRHI::ValidateRequiredLayersAndExtensions(
  const std::vector<std::string>& req_layers,
  const std::vector<std::string>& req_extensions,
  const std::unordered_set<std::string>& available_layers,
  const std::unordered_set<std::string>& available_extensions
) {
  // Validate required layers
  bool all_layers_available{ true };
  for (const auto& req_layer : req_layers) {
    if (available_layers.contains(req_layer)) {
      MAPLE_LOG_INFO(LogRHI, "Found required Vulkan layer: {}", req_layer);
    } else {
      MAPLE_LOG_CRITICAL(LogRHI, "Required Vulkan layer not available: {}",
                                 req_layer);
      all_layers_available = false;
    }
  }

  // Validate required extensions
  bool all_extensions_available{ true };
  for (const auto& req_extension : req_extensions) {
    if (available_extensions.contains(req_extension)) {
      MAPLE_LOG_INFO(LogRHI, "Found required Vulkan instance extension: {}",
                             req_extension);
    } else {
      MAPLE_LOG_CRITICAL(LogRHI, "Required Vulkan instance extension not "
                                 "available: {}", req_extension);
      all_extensions_available = false;
    }
  }

  // Abort if any required layers or extensions are unavailable
  if (!all_layers_available || !all_extensions_available) {
    const std::string msg{ "One or more required Vulkan layers or extensions "
                           "are unavailable" };
    MAPLE_LOG_CRITICAL(LogRHI, msg);
    throw std::runtime_error{ msg };
  }
}

std::pair<std::vector<std::string>, std::vector<std::string>>
VulkanRHI::ValidateOptionalLayersAndExtensions(
  const std::vector<std::string>& opt_layers,
  const std::vector<std::string>& opt_extensions,
  const std::unordered_set<std::string>& available_layers,
  const std::unordered_set<std::string>& available_extensions
) {
  std::vector<std::string> validated_layers{};
  std::vector<std::string> validated_extensions{};

  // Validate optional layers and keep only available ones
  for (const auto& opt_layer : opt_layers) {
    if (available_layers.contains(opt_layer)) {
      MAPLE_LOG_INFO(LogRHI, "Found optional Vulkan layer: {}", opt_layer);
      validated_layers.emplace_back(opt_layer);
    } else {
      MAPLE_LOG_WARN(LogRHI, "Optional Vulkan layer not available: {}; "
                             "skipping", opt_layer);
    }
  }

  // Validate optional extensions and keep only available ones
  for (const auto& opt_extension : opt_extensions) {
    if (available_extensions.contains(opt_extension)) {
      MAPLE_LOG_INFO(LogRHI, "Found optional Vulkan instance extension: {}",
                             opt_extension);
      validated_extensions.emplace_back(opt_extension);

      // Track device address binding extension availability separately
      if (opt_extension == VK_EXT_DEVICE_ADDRESS_BINDING_REPORT_EXTENSION_NAME) {
        device_address_binding_available_ = true;
      }
    } else {
      MAPLE_LOG_WARN(LogRHI, "Optional Vulkan instance extension not "
                             "available: {}; skipping", opt_extension);
    }
  }

  return std::make_pair(validated_layers, validated_extensions);
}

void VulkanRHI::CreateDebugMessenger() {
  MAPLE_LOG_INFO(LogRHI, "Creating Vulkan debug messenger...");

  // Configure which message severities to capture
  constexpr vk::DebugUtilsMessageSeverityFlagsEXT message_severities{
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo |
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning |
    vk::DebugUtilsMessageSeverityFlagBitsEXT::eError
  };

  // Configure debug messenger message types based on available extensions
  vk::DebugUtilsMessageTypeFlagsEXT message_types =
    vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
    vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation |
    vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance;

  // Add device address binding messages if extension is available
  if (device_address_binding_available_) {
    message_types |= vk::DebugUtilsMessageTypeFlagBitsEXT::eDeviceAddressBinding;
  }

  // Configure debug messenger to capture all message severities and types
  const vk::DebugUtilsMessengerCreateInfoEXT create_info{
    .messageSeverity = message_severities,
    .messageType = message_types,
    .pfnUserCallback = DebugCallback
  };

  // Create debug messenger and attach to instance
  debug_messenger_ = instance_->createDebugUtilsMessengerEXTUnique(create_info);

  MAPLE_LOG_INFO(LogRHI, "Vulkan debug messenger created");
}

VKAPI_ATTR vk::Bool32 VKAPI_CALL VulkanRHI::DebugCallback(
  vk::DebugUtilsMessageSeverityFlagBitsEXT severity,
  vk::DebugUtilsMessageTypeFlagsEXT type,
  const vk::DebugUtilsMessengerCallbackDataEXT* callback_data,
  void* user_data
) {
  // Route validation layer messages to the logging system based on severity
  switch (severity) {
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose:
      MAPLE_LOG_DEBUG(LogRHI, callback_data->pMessage);
      break;
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo:
      MAPLE_LOG_INFO(LogRHI, callback_data->pMessage);
      break;
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning:
      MAPLE_LOG_WARN(LogRHI, callback_data->pMessage);
      break;
    case vk::DebugUtilsMessageSeverityFlagBitsEXT::eError:
      MAPLE_LOG_ERROR(LogRHI, callback_data->pMessage);
      break;
  }

  // Return false to indicate we should not abort on validation errors
  return vk::False;
}

} // namespace maple::rhi
