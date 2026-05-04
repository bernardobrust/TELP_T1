#pragma once

#include <algorithm>
#include <array>
#include <utility>

#include "Ball.hxx"
#include "Cue.hxx"
#include "raylib.h"

struct App {
  static constexpr unsigned window_width = 800;
  static constexpr unsigned window_height = 600;
  static constexpr unsigned fps_target = 240;

  static constexpr Color background_color = BLACK;

  std::array<Ball, 5> balls{
      Ball(10.0, 10.0, 2.0, 2.0),  Ball(50.0, 10.0, 2.0, 2.0),
      Ball(100.0, 30.0, 2.0, 2.0), Ball(170.0, 50.0, 2.0, 2.0),
      Ball(400.0, 70.0, 2.0, 2.0),
  };

  Cue cue{400, 300};

  auto inline tick() -> void {
    std::ranges::for_each(balls, [](auto& e) { e.update(); });

    cue.update();
  }

  auto inline render() -> void {
    BeginDrawing();

    std::ranges::for_each(std::as_const(balls),
                          [](const auto& e) { e.draw(); });

    cue.draw();

    ClearBackground(background_color);

    EndDrawing();
  }

  auto inline init() -> void {
    InitWindow(window_width, window_height, "Bilhar");
    SetTargetFPS(240);
  }

  auto inline run() -> void {
    while (!WindowShouldClose()) {
      tick();
      render();
    }
  }

  auto inline cleanup() -> int {
    CloseWindow();

    return 0;
  }
};