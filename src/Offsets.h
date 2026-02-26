#pragma once

#include <cstdint>

/**
 * RePhiEdit Offsets Configuration
 *
 * This file contains hardcoded memory addresses for the target application.
 * When the original application updates, these addresses must be verified and
 * updated.
 *
 * Calculation method: (IDA Absolute Address) - (Image Base, default 0x400000)
 * Example: IDA shows dword_7032C4 -> 0x7032C4 - 0x400000 = 0x3032C4
 */

namespace Offsets {

// Shader system initialization function (sub_46CC60)
// Responsible for pre-loading built-in shaders and setting up uniform maps.
constexpr uintptr_t INIT_FUNCTION = 0x6CC60;

// Pointer to the global std::vector<std::string> containing shader names.
// Index mapping: [0-9] Base shaders, [10-19] Variant 2 shaders.
constexpr uintptr_t SHADER_NAMES_VECTOR = 0x3032C4;

// Pointer to the global std::vector<std::string> containing uniform variables.
// Used by the engine to map shader uniform names to internal IDs.
constexpr uintptr_t UNIFORM_NAMES_VECTOR = 0x304A54;

} // namespace Offsets
