#include "App.hxx"

#include <raylib.h>

#include <algorithm>
#include <array>
#include <utility>

#include "Ball.hxx"
#include "Cue.hxx"

constexpr unsigned window_width = 800;
constexpr unsigned window_height = 600;
constexpr unsigned fps_target = 240;

constexpr auto background_color = BLACK;

static std::array balls{
    Ball(10.0, 10.0, 2.0, 2.0),  Ball(50.0, 10.0, 2.0, 2.0),
    Ball(100.0, 30.0, 2.0, 2.0), Ball(170.0, 50.0, 2.0, 2.0),
    Ball(400.0, 70.0, 2.0, 2.0),
};

static Cue cue(400, 300);

auto App::tick() -> void {
  std::ranges::for_each(balls, [](auto& e) { e.update(); });

  cue.update();
}

auto App::render() -> void {
  BeginDrawing();

  std::ranges::for_each(std::as_const(balls), [](const auto& e) { e.draw(); });

  cue.draw();

  ClearBackground(background_color);

  EndDrawing();
}

auto App::init() -> void {
  InitWindow(window_width, window_height, "Bilhar");
  SetTargetFPS(240);
}

auto App::run() -> void {
  while (!WindowShouldClose()) {
    tick();
    render();
  }
}

auto App::cleanup() -> int {
  CloseWindow();

  return 0;
}
