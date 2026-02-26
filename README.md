# RePhiEdit Shader Injector

A robust DLL proxy for `zlib1.dll` designed to inject custom shaders into the RePhiEdit game engine. It hooks internal initialization functions to dynamically register user-defined `.glsl` and `.fsh` files.

## Features

- **Transparent Proxying**: Intercepts `zlib1.dll` calls and forwards them to the original library (renamed to `zlib0.dll`).
- **Dynamic Shader Injection**: Scans `Resources/shaders/` for custom effects at runtime.
- **Engine Compatibility**: Automatically handles engine-specific registration requirements, including shader variants (`_2`) and uniform parameter parsing.
- **Maintainable Architecture**: Centralized memory offsets in `src/Offsets.h` for quick updates after game patches.
- **Robust Hooking**: Uses [MinHook](https://github.com/TsudaKageyu/minhook) for reliable instruction-level hooking with proper calling convention handling.

## Quick Start / Deployment

1. **Prerequisites**: Ensure you have the compiled `zlib1.dll`.
2. **Rename Original**: In the game directory, find the original `zlib1.dll` and rename it to **`zlib0.dll`**.
3. **Inject Proxy**: Copy your custom-built **`zlib1.dll`** into the game directory.
4. **Add Shaders**: Place your custom `.glsl` or `.fsh` shader files into the `Resources/shaders/` folder.
5. **Launch**: Start the game normally.

## Custom Shaders

The injector looks for `uniform` declarations in your shader files (e.g., `uniform float power;`) and automatically registers them with the engine's parameter system.

Each custom shader `my_shader` will be available as:

1. `my_shader` (Base layer)
2. `my_shader_2` (Second layer/variant, required for engine saving)

## Building from Source

### Requirements

- CMake (3.15+)
- Visual Studio 2019/2022 with C++ Desktop Development (Recommended) or another MSVC-compatible toolchain

Run the provided `build.bat` in a terminal:

```batch
# Build release version (Win32)
build.bat clean release

# Build debug version (Win32)
build.bat debug
```

> [!NOTE]
> This script uses CMake to configure the project for MSVC. Using CMake ensures that all library headers (like `MinHook.h`) are correctly found during the build process.

```bash
# Generate build files for MSVC (Win32)
cmake -S . -B build -A Win32
# Build the project
cmake --build build --config Release
```

## Project Structure

- `src/ZLibProxy.cpp`: Main proxy entry point and export forwarding.
- `src/ShaderInjector.cpp`: Logic for scanning directories and patching engine vectors.
- `src/Offsets.h`: Centralized memory addresses for the target version.
- `libs/minhook`: MinHook library for hooking.
- `build.bat`: Ease-of-use build automation.

## Updating for New Versions

If RePhiEdit updates and the injector stops working:

1. Use a tool like IDA Pro or Ghidra to find the new addresses for:
   - `sub_46CC60` (Init function)
   - Shader names vector
   - Uniform names vector
2. Update the hex values in `src/Offsets.h`.
3. Rebuild and redeploy.

## Continuous Integration (CI/CD)

This project includes a GitHub Actions workflow that automatically builds and releases the `zlib1.dll` whenever you:

- Push code to the `main` or `master` branch.
- Push a version tag (e.g., `git tag v1.0` followed by `git push --tags`).

You can find the compiled binaries in the **Actions** or **Releases** tab of your GitHub repository.
