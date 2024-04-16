#include "bkout.c"
#include "pong.c"
#include <raylib.h>

void mainWindow() {
    InitWindow(600, 600, "Make Commands");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Press 1 to play PONG", 150, 150, 30, WHITE);
        DrawText("Press 2 to play Breakout", 150, 200, 30, WHITE);
        DrawText("Press ESC to exit", 150, 250, 30, WHITE);

        if (IsKeyPressed(KEY_ESCAPE))
            CloseWindow();
        else if (IsKeyPressed(KEY_ONE)) {
            CloseWindow();
            pong();
            mainWindow();
        } else if (IsKeyPressed(KEY_TWO)) {
            CloseWindow();
            breakout();
            mainWindow();
        }

        EndDrawing();
    }
    CloseWindow();
}

int main() {
    mainWindow();
    return 0;
}
