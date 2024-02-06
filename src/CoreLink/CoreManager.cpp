// Mouse movement callback
#include "CoreManager.h"

#include "GLFW/glfw3.h"
#include <imgui.h>
#include "imgui_impl_glfw.h"

CoreManager::CoreManager() { QLogger::GetInstance().Log(LOGLEVEL::TRACE, "CoreManager::CoreManager"); }

CoreManager::~CoreManager() { loader.unloadLibrary(); }

void CoreManager::update() {}

// Load shared library core and initialise
void CoreManager::loadCore(const std::string &filePath) {
  QLogger::GetInstance().Log(LOGLEVEL::INFO, "Loading core: ", filePath);

  if (loader.loadLibrary(filePath)) {
    QLogger::GetInstance().Log(LOGLEVEL::INFO, "Loaded library!");

    LibraryType::init init = loader.getFunction<LibraryType::init>("core_init");
    if (init != nullptr) {
      if (!init()) {
        QLogger::GetInstance().Log(LOGLEVEL::ERR, "Core failed initialisation!");
      }
    }

  } else {
    QLogger::GetInstance().Log(LOGLEVEL::ERR, "Failed to load library!", dlerror());
  }
}

// Callback to log GL errors
void CoreManager::GLFWErrorCallBack(int, const char *err_str) { QLogger::GetInstance().Log(LOGLEVEL::ERR, err_str); }

void GLAPIENTRY CoreManager::MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
                                             const GLchar *message, const void *userParam) {
  fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
          (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""), type, severity, message);
}