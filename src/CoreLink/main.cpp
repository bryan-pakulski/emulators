#include "Display/QDisplay.h"
#include "CoreManager.h"

#include <imgui_impl_glfw.h>
#include <memory>

int main() {

  std::srand(std::time(nullptr));

  while (!glfwWindowShouldClose(QDisplay::GetInstance().getWindow())) {

    // Clean OpenGL frame & imgui interface
    QDisplay::clearFrame();

    QDisplay::GetInstance().drawMenus();

    // Core Manager loop (logic & graphics rendering)
    CoreManager::GetInstance().update();

    // Process and catch events, draw ui
    QDisplay::processFrameAndEvents();
  }

  return 0;
}