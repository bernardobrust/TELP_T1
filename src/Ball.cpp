#include "Ball.hxx"

auto Ball::update() -> void {
  m_pos_x += m_vel_x;
  m_pos_y += m_vel_y;
}

auto Ball::draw() const -> void {
  DrawCircle(m_pos_x, m_pos_y, radius, ball_color);
}
