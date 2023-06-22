#include <raylib.h>

int main() {
    InitWindow(600, 600, "Make Commands");
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("You can use make followed by", 50, 150, 30, WHITE);
        DrawText("break for breakout", 150, 200, 30, WHITE);
        DrawText("pong for pong", 150, 250, 30, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
