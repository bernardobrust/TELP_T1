#include "Cue.hxx"

#include "raylib.h"

auto Cue::update() -> void {
  const auto [x, y] = GetMousePosition();
  m_pos.first = x - (width / 2);
  m_pos.second = y - (height / 2);
}
