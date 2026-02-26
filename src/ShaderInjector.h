#pragma once

/**
 * Hook function declaration and the corresponding original function pointer.
 */

/**
 * Hooked function for shader loading (sub_46CC60).
 * Uses __fastcall to preserve registers on x86, including the dummy EDX
 * parameter.
 */
void *__fastcall ShaderLoader_Sub46CC60(void *this_ptr, void *edx_unused);

/**
 * Typedef for the original function pointer.
 * Matches the hooked function signature exactly.
 */
typedef void *(__fastcall *Sub46CC60_Func)(void *this_ptr, void *edx_unused);

// Extern pointer to the original function, initialized in initialization flow.
extern Sub46CC60_Func original_Sub46CC60;