//
// Created by be on 3/27/26.
//

#include "Cue.h"

#include "raylib.h"

auto Cue::update() -> void {
    const auto [x, y] = GetMousePosition();
    m_pos_x = x - (width / 2);
    m_pos_y = y - (height / 2);
}

auto Cue::draw() const -> void {
    DrawRectangle(m_pos_x, m_pos_y, width, height, cue_color);
}

