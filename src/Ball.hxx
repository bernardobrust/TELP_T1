#pragma once

#include <utility>

#include "raylib.h"

class Ball {
  std::pair<float, float> m_pos{}, m_vel{};

 public:
  static constexpr float radius{6.0};
  static constexpr auto ball_color = RAYWHITE;

  explicit Ball(const float x, const float y, const float vel_x,
                const float vel_y)
      : m_pos(x, y), m_vel(vel_x, vel_y) {}
  ~Ball() = default;

  [[nodiscard]] float get_pos_x() const { return m_pos.first; }
  [[nodiscard]] float get_pos_y() const { return m_pos.second; }

  auto update() -> void;
  auto draw() const -> void;
};
