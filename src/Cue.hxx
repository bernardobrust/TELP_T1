#pragma once

#include <utility>

#include "raylib.h"

class Cue {
  std::pair<float, float> m_pos{};

 public:
  static constexpr float width{10.0}, height{130.0};
  static constexpr auto cue_color = BROWN;

  explicit Cue(const float x, const float y) : m_pos(x, y) {}
  ~Cue() = default;

  [[nodiscard]] float get_pos_x() const { return m_pos.first; }
  [[nodiscard]] float get_pos_y() const { return m_pos.second; }

  auto update() -> void;
  auto draw() const -> void;
};