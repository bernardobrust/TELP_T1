#pragma once

#include "raylib.h"

class Cue {
  float m_pos_x{}, m_pos_y{};

 public:
  static constexpr float width{10.0}, height{130.0};
  static constexpr auto cue_color = BROWN;

  explicit Cue(const float x, const float y) : m_pos_x{x}, m_pos_y{y} {}
  ~Cue() = default;

  [[nodiscard]] float get_pos_x() const { return m_pos_x; }

  [[nodiscard]] float get_pos_y() const { return m_pos_y; }

  auto update() -> void;
  auto draw() const -> void;
};