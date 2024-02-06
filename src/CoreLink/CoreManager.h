#pragma once

#include <dlfcn.h>
#include "GLFW/glfw3.h"
#include "QLogger.h"
#include <memory>
#include <vector>

namespace LibraryType {
using init = bool (*)();
};

class LibraryLoader {
private:
  void *libraryHandle;

public:
  LibraryLoader() : libraryHandle(nullptr) {}

  bool loadLibrary(const std::string &libraryPath) {
    libraryHandle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    return libraryHandle != nullptr;
  }

  void unloadLibrary() {
    if (libraryHandle != nullptr) {
      dlclose(libraryHandle);
      libraryHandle = nullptr;
    }
  }

  template <typename FuncType> FuncType getFunction(const std::string &functionName) {
    if (libraryHandle != nullptr) {
      void *func = dlsym(libraryHandle, functionName.c_str());
      return reinterpret_cast<FuncType>(func);
    }
    return nullptr;
  }
};

class CoreManager {

public:
  static CoreManager &GetInstance() {
    static CoreManager s_CoreManager;
    return s_CoreManager;
  }

  // Prohibit external replication constructs
  CoreManager(CoreManager const &) = delete;
  // Prohibit external assignment operations
  void operator=(CoreManager const &) = delete;

  // Main update loop
  void update();

  void loadCore(const std::string &filePath);

  /*
    CALLBACKS
  */
  // Recalculate frame buffer on window resize
  static void GLFWErrorCallBack(int, const char *err_str);
  static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                         const GLchar *message, const void *userParam);

private:
  LibraryLoader loader;

  // TODO: add core state to allow loading roms / restarting emulation

private:
  explicit CoreManager();
  ~CoreManager();

  // Process inputs
  void logicLoop();
  // Render loop
  void renderLoop();
};