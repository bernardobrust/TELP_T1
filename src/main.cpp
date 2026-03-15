//
// Created by be on 3/15/26.
//

#include <raylib.h>

auto main() -> int {
    InitWindow(640, 480, "Bilhar");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLACK);

        EndDrawing();
    }

    CloseWindow();
}
