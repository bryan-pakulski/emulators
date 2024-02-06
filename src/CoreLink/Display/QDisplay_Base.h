#pragma once

#include <fstream>
#include <imgui.h>
#include <memory>

#include "GLFW/glfw3.h"
#include "QLogger.h"

// Basic menu class
// QDisplay uses this base class as a reference via smart pointer, this is to
// call the overloaded virtual render function

struct listItem {
  std::string m_name;
  std::string m_key;
  bool m_isSelected = false;
};

inline bool operator==(const ImVec2 &a, const ImVec2 &b) {
  float epsilon = 0.01f;
  return (fabs(a.x - b.x) < epsilon) && (fabs(a.y - b.y) < epsilon);
}

class QDisplay_Base {

public:
  bool m_isOpen = false;
  std::string m_windowName;

public:
  QDisplay_Base(GLFWwindow *w) : m_window(w) {}
  virtual void render() {}

protected:
  GLFWwindow *m_window;
  ImGuiWindowClass m_window_class;

protected:
  void getWindowSize(std::pair<int, int> &size) { glfwGetFramebufferSize(m_window, &size.first, &size.second); }
};
