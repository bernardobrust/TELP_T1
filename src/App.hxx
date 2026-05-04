#pragma once

#include <algorithm>
#include <array>
#include <utility>

#include "Ball.hxx"
#include "Cue.hxx"
#include "raylib.h"

// TODO: Check if the order of the member data is adequate
struct App {
  std::array<Ball, 5> balls{
      Ball(10.0f, 10.0f, 2.0f, 2.0f),  Ball(50.0f, 10.0f, 2.0f, 2.0f),
      Ball(100.0f, 30.0f, 2.0f, 2.0f), Ball(170.0f, 50.0f, 2.0f, 2.0f),
      Ball(400.0f, 70.0f, 2.0f, 2.0f),
  };

  Cue cue{400.0f, 300.0f};

  static constexpr unsigned window_width{800}, window_height{600},
      fps_target{240};
  static constexpr Color background_color{BLACK};

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
    SetTargetFPS(fps_target);
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