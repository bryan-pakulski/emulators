#pragma once

#include "CoreManager.h"

#include <imgui.h>
#include "ThirdParty/imgui/imfilebrowser.h"
#include "Display/QDisplay_Base.h"

#include <imgui_stdlib.h>

class LoadCore : public QDisplay_Base {
public:
  LoadCore(GLFWwindow *w) : QDisplay_Base(w) {
    fileDialog.SetTitle("Load Core");
    fileDialog.SetTypeFilters({".ecore"});
  }

  void openWindow() { fileDialog.Open(); };

  virtual void render() {
    fileDialog.Display();
    if (fileDialog.HasSelected()) {
      CoreManager::GetInstance().loadCore(fileDialog.GetSelected().string());
      clear();
    }
  }

private:
  ImGui::FileBrowser fileDialog;

private:
  void clear() { fileDialog.ClearSelected(); }
};