#include "Cue.hxx"

#include "raylib.h"

auto Cue::update() -> void {
  const auto [x, y] = GetMousePosition();
  m_pos.first = x - (width / 2);
  m_pos.second = y - (height / 2);
}

auto Cue::draw() const -> void {
  DrawRectangle(m_pos.first, m_pos.second, width, height, cue_color);
}
