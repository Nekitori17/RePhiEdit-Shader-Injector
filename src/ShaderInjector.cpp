#include "ShaderInjector.h"
#include "Offsets.h"
#include <filesystem>
#include <fstream>
#include <regex>
#include <string>
#include <vector>
#include <windows.h>


namespace fs = std::filesystem;

// Stores the original function pointer to call after our hook logic
Sub46CC60_Func original_Sub46CC60 = nullptr;

/**
 * Scans a GLSL/FSH shader file for 'uniform' declarations.
 * Adds newly found uniform names to the global engine variable vector.
 */
void ParseUniforms(std::vector<std::string> *varVector,
                   const fs::path &filePath) {
  std::ifstream file(filePath);
  if (!file.is_open()) {
    return;
  }

  std::string line;
  // Regex to match "uniform type name;"
  static std::regex uniformRegex(R"(uniform\s+\w+\s+(\w+)\s*;)");
  std::smatch match;

  while (std::getline(file, line)) {
    if (std::regex_search(line, match, uniformRegex)) {
      std::string varName = match[1];

      // Avoid adding duplicate uniform names to the vector
      bool exists = false;
      for (const auto &existing : *varVector) {
        if (existing == varName) {
          exists = true;
          break;
        }
      }
      if (!exists) {
        varVector->push_back(varName);
      }
    }
  }
}

/**
 * Hooked version of the engine's shader initialization function.
 * This runs after the game has registered its default shaders.
 */
void *__fastcall ShaderLoader_Sub46CC60(void *this_ptr, void *edx_unused) {
  // First, let the original function finish its work
  void *result = original_Sub46CC60(this_ptr, nullptr);

  uintptr_t baseAddr = (uintptr_t)GetModuleHandle(NULL);

  // Access internal engine vectors via the verified offsets
  auto globalShaderVector =
      (std::vector<std::string> *)(baseAddr + Offsets::SHADER_NAMES_VECTOR);
  auto globalVarVector =
      (std::vector<std::string> *)(baseAddr + Offsets::UNIFORM_NAMES_VECTOR);

  // Scan for custom shaders in the Resources/shaders directory
  std::string shaderPath = "Resources/shaders";
  if (fs::exists(shaderPath)) {
    for (const fs::directory_entry &entry :
         fs::directory_iterator(shaderPath)) {
      if (entry.is_regular_file() && (entry.path().extension() == ".glsl" ||
                                      entry.path().extension() == ".fsh")) {

        std::string fileName = entry.path().stem().string();

        // Check if this shader is already registered
        bool alreadyHas = false;
        for (const auto &s : *globalShaderVector) {
          if (s == fileName) {
            alreadyHas = true;
            break;
          }
        }

        if (!alreadyHas) {
          // Register the base shader name
          globalShaderVector->push_back(fileName);

          // Register the variant '_2' which is required for the engine's
          // layering/save system
          globalShaderVector->push_back(fileName + "_2");

          // Parse the shader file to find and register uniform variables
          ParseUniforms(globalVarVector, entry.path());
        }
      }
    }
  }
  return result;
}