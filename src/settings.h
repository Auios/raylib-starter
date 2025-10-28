#pragma once

#include <fstream>
#include <nlohmann/json.hpp>
#include <string>

namespace settings {
  struct Settings {
    std::string version = "0.0.1";
    int screenWidth = 800;
    int screenHeight = 600;
    int targetFps = 100;
  };

  template <typename JsonType> inline void to_json(JsonType& j, const Settings& s) {
    j = {
        {"version", s.version},
        {"screenWidth", s.screenWidth},
        {"screenHeight", s.screenHeight},
        {"targetFps", s.targetFps}};
  }

  inline void from_json(const nlohmann::json& j, Settings& s) {
    j.at("version").get_to(s.version);
    j.at("screenWidth").get_to(s.screenWidth);
    j.at("screenHeight").get_to(s.screenHeight);
    j.at("targetFps").get_to(s.targetFps);
  }

  inline std::string getSettingsPath() { return "settings.json"; }

  inline bool save(const Settings& settings) {
    std::ofstream file(getSettingsPath());
    if (!file.is_open())
      return false;
    nlohmann::ordered_json j = settings;
    file << j.dump(2);
    file.close();
    return true;
  }

  inline Settings load() {
    std::ifstream file(getSettingsPath());
    if (!file.is_open()) {
      return Settings{};
    }
    nlohmann::json j;
    file >> j;
    file.close();
    return j.get<Settings>();
  }
} // namespace settings