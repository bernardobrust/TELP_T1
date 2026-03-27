//
// Created by be on 3/22/26.
//

#include "App.h"

#include <raylib.h>

#include "add_vecs.h"
#include "Ball.h"

constexpr size_t window_width = 800;
constexpr size_t window_height = 600;
constexpr size_t fps_target = 240;

constexpr auto ball_color = RAYWHITE;
constexpr auto background_color = BLACK;

static std::array balls {
    Ball(10.0, 10.0, 2.0, 2.0),
    Ball(50.0, 10.0, 2.0, 2.0),
    Ball(100.0, 30.0, 2.0, 2.0),
    Ball(170.0, 50.0, 2.0, 2.0),
    Ball(400.0, 70.0, 2.0, 2.0),
};

auto App::tick() -> void {
    // Empty for now
}

auto App::render() -> void {
    BeginDrawing();

    std::ranges::for_each(std::as_const(balls), [](const auto &e) {
        DrawCircle(e.get_pos_x(), e.get_pos_y(), Ball::radius, ball_color);
    });

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
