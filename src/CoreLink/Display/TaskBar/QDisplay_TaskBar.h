#pragma once

#include "Config/config.h"
#include "QLogger.h"
#include "Display/QDisplay_Base.h"

#include "LoadCore.h"

#include <fstream>
#include <imgui.h>
#include <imgui_stdlib.h>
#include <memory>

class QDisplay_TaskBar : public QDisplay_Base {
public:
  QDisplay_TaskBar(GLFWwindow *w) : QDisplay_Base(w) { m_loadCoreWindow = std::unique_ptr<LoadCore>(new LoadCore(w)); }

  /*
   * Main Menu renderer, contains logic for showing additional display items
   */
  virtual void render() {
    if (ImGui::BeginMainMenuBar()) {

      if (ImGui::BeginMenu("File")) {

        if (ImGui::MenuItem("Load Core")) {
          m_loadCoreWindow->openWindow();
        }

        ImGui::EndMenu();
      }

      // TODO: if core is loaded allow us to load roms

      if (ImGui::BeginMenu("Debug")) {

        if (ImGui::MenuItem("Open Log")) {
          logFileOpen = true;
        }

        ImGui::EndMenu();
      }

      ImGui::EndMainMenuBar();
    }

    // These will only render if their corresponding flags are set
    QDisplay_LogFile();

    m_loadCoreWindow->render();
  }

private:
  // Windows
  std::unique_ptr<LoadCore> m_loadCoreWindow;

  // Window triggers
  bool logFileOpen = false;

  // Log config
  std::ifstream logStream;
  std::stringstream logFileBuffer;
  bool logUpdated = true;
  clock_t lastLogReadTime;

  // New file config
  std::string m_canvasName = "new";

private:
  /*
   * Popup for displaying log file output
   */
  void QDisplay_LogFile() {

    if (logFileOpen) {
      ImGui::SetNextWindowBgAlpha(0.9f);
      ImGui::Begin("Log");

      if (ImGui::Button("Close")) {
        logFileOpen = false;
      }

      ImGui::SameLine();

      if (ImGui::Button("Clear")) {
        logStream.close();
        QLogger::GetInstance().resetLog();
      }

      ImGui::Separator();

      ImGui::BeginChild("ScrollingLog");

      // Only update text if required
      if (QLogger::GetInstance().m_LAST_WRITE_TIME != lastLogReadTime) {
        logStream.open(CONFIG::LOG_FILE.get(), std::ios::in);

        logFileBuffer.clear();
        logFileBuffer.str(std::string());

        lastLogReadTime = QLogger::GetInstance().m_LAST_WRITE_TIME;
        logFileBuffer << logStream.rdbuf();
        logStream.close();
        logUpdated = true;
      }

      // ImGui::TextWrapped("%s", logFileBuffer.str().c_str());
      ImGui::TextUnformatted(logFileBuffer.str().c_str());

      // Move to bottom of screen
      if (logUpdated) {
        ImGui::SetScrollY(ImGui::GetScrollMaxY() + ImGui::GetStyle().ItemSpacing.y * 2);
        logUpdated = false;
      }
      ImGui::EndChild();

      ImGui::End();
    }
  }
};