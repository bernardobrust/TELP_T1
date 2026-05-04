#pragma once

#include <numbers>
#include <utility>

#include "AABB2D.hxx"
#include "raylib.h"

class Ball {
 private:
  std::pair<float, float> m_pos{}, m_vel{};
  static constexpr float radius{6.0}, pi{std::numbers::pi};

 public:
  static constexpr auto ball_color = RAYWHITE;

  explicit Ball(const float x, const float y, const float vel_x,
                const float vel_y)
      : m_pos(x, y), m_vel(vel_x, vel_y) {}
  ~Ball() = default;

  [[nodiscard]] inline float get_pos_x() const { return m_pos.first; }
  [[nodiscard]] inline float get_pos_y() const { return m_pos.second; }
  [[nodiscard]] inline float get_radius() const { return radius; }

  auto inline contains_point(const float x, const float y) -> bool const {
    const float dx = x - m_pos.first, dy = y - m_pos.second;
    return dx * dx + dy * dy <= radius * radius;
  }

  // Smallest AABB enclosing the circle
  auto to_aabb() -> AABB2D const {
    return AABB2D(m_pos.first - radius, m_pos.second - radius,
                  m_pos.first + radius, m_pos.second + radius);
  }

  auto update() -> void;
  auto draw() const -> void;
};
