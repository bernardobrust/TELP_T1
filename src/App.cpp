//
// Created by be on 3/22/26.
//

#include "App.h"

#include <raylib.h>

#include "add_vecs.h"

constexpr size_t window_width = 800;
constexpr size_t window_height = 600;
constexpr size_t fps_target = 240;

constexpr auto ball_color = RAYWHITE;
constexpr auto background_color = BLACK;

auto App::tick() -> void {
    // Empty for now
}

auto App::render() -> void {
    BeginDrawing();

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
