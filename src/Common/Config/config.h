#pragma once

#include <fstream>
#include <yaml-cpp/yaml.h>
#include <yaml-cpp/exceptions.h>

#include "types.h"

namespace CONFIG {

static YAML::Node configFile = YAML::LoadFile("data/config.yaml");

// Load config with default value if item doesn't exist
template <class T> static T loadConfig(const std::string &configPath, const T &defaultValue) {
  try {
    return configFile[configPath].as<T>();
  } catch (const YAML::Exception &) {
    return defaultValue;
  }
}

// ImGui configuration
static CString PROGRAM_NAME("CoreLink");
static CFloat HIGH_DPI_SCALE_FACTOR(loadConfig<float>("HIGH_DPI_SCALE_FACTOR", 1.0f));
static CInt WINDOW_WIDTH(loadConfig("WINDOW_WIDTH", 720));
static CInt WINDOW_HEIGHT(loadConfig("WINDOW_HEIGHT", 640));

static CFloat IMGUI_TOOLS_WINDOW_WIDTH(loadConfig("IMGUI_TOOLS_WINDOW_WIDTH", 380.0f));
static CFloat IMGUI_TOOLS_WINDOW_MIN_WIDTH(loadConfig("IMGUI_TOOLS_WINDOW_MIN_WIDTH", 64.0f));
static CFloat IMGUI_TOP_WINDOW_HEIGHT(loadConfig("IMGUI_TOP_WINDOW_HEIGHT", 18.0f));

static CFloat IMGUI_LOG_WINDOW_HEIGHT(loadConfig("IMGUI_LOG_WINDOW_HEIGHT", 480.0f));
static CFloat IMGUI_LOG_WINDOW_WIDTH(loadConfig("IMGUI_LOG_WINDOW_WIDTH", 320.0f));

// Logging
static CInt ENABLE_GL_DEBUG(loadConfig<int>("ENABLE_OPENGL_DEBUG_OUTPUT", 0));
static CInt ENABLE_TRACE_LOGGING(loadConfig<int>("ENABLE_TRACE_LOGGING", 0));
static CInt DEBUG_LEVEL(loadConfig<int>("DEBUG_LEVEL", 5));
static CString LOG_FILE(loadConfig<std::string>("LOG_FILE", "data/CoreLink.log"));

} // namespace CONFIG