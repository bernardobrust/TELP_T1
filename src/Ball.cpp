#include "Ball.hxx"

auto Ball::update() -> void {
  m_pos.first += m_vel.first;
  m_pos.second += m_vel.second;
}
