#include "Ball.hxx"

auto Ball::update() -> void {
  m_pos.first += m_vel.first;
  m_pos.second += m_vel.second;
}

auto Ball::draw() const -> void {
  DrawCircle(m_pos.first, m_pos.second, radius, ball_color);
}
