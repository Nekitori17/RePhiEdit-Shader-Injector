#include "ModLoader.h"
#include "MinHook.h"
#include "Offsets.h"
#include "ShaderInjector.h"
#include <windows.h>


/**
 * Main initialization logic for the mod loader.
 * Sets up API hooking using MinHook.
 */
void ModLoader::Initialize() {
  // Initialize MinHook library
  if (MH_Initialize() != MH_OK) {
    return;
  }

  // Get the base address of the current process (the game)
  uintptr_t baseAddr = (uintptr_t)GetModuleHandle(NULL);

  // Create a hook on the shader system initialization function
  if (MH_CreateHook((LPVOID)(baseAddr + Offsets::INIT_FUNCTION),
                    (LPVOID)&ShaderLoader_Sub46CC60,
                    (LPVOID *)&original_Sub46CC60) != MH_OK) {
    return;
  }

  // Enable all registered hooks
  MH_EnableHook(MH_ALL_HOOKS);
}