#pragma once

#include <utility>

#include "raylib.h"

class Cue {
  std::pair<float, float> m_pos{};
  static constexpr float width{10.0f}, height{130.0f};
  static constexpr Color cue_color = BROWN;

 public:
  explicit Cue(const float x, const float y) : m_pos(x, y) {}
  ~Cue() = default;

  [[nodiscard]] inline float get_pos_x() const { return m_pos.first; }
  [[nodiscard]] inline float get_pos_y() const { return m_pos.second; }

  auto update() -> void;
  auto inline draw() const -> void {
    DrawRectangle(m_pos.first, m_pos.second, width, height, cue_color);
  }
};