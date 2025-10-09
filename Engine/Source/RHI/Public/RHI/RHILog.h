#pragma once

// Core
#include "Core/Log.h"

// RHI
#include "RHI/RHIAPI.h"

/**
 * @brief Log category for RHI (Render Hardware Interface) module messages.
 *
 * Used for logging graphics backend operations, resource creation,
 * command submission, and rendering-related functionality.
 */
MAPLE_DECLARE_LOG_CATEGORY(MAPLE_RHI_API, LogRHI);
