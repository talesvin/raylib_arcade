#include <raylib.h>

const int screenWidth = 800;
const int screenHeight = 800;
const char *title = "Breakout";

struct Player {
    int x;
    int y;
    int w;
    int h;
    Color c;
};

struct Ball {
    int x;
    int y;
    int r;
    Color c;
    double x_speed;
    double y_speed;
};

typedef struct Rect {
    int x;
    int y;
    int width;
    int height;
    Color color;
} Rect;

int ballDirection(int min, int max) {
    int value = GetRandomValue(min, max);
    if (value < -5 || value > 5)
        return value;
    return ballDirection(min, max);
}

Rect updatePieces(int l, int p, Rect pieces[l][p], int pos_p, int pos_l) {
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < p; j++) {
            if (j != 0)
                pos_p = pieces[i][j - 1].x + 70;
            pieces[i][j].x = pos_p;
            pieces[i][j].y = pos_l;
            pieces[i][j].width = 60;
            pieces[i][j].height = 20;
            if (i == 0 || i == 4)
                pieces[i][j].color = YELLOW;
            else if (i == 1 || i == 5)
                pieces[i][j].color = GREEN;
            else if (i == 2 || i == 6)
                pieces[i][j].color = RED;
            else if (i == 3 || i == 7)
                pieces[i][j].color = BLUE;
        }
        if (pos_l > 210)
            pos_l = 0;
        pos_l += 30;
        pos_p = 20;
    }
    return pieces[l][p];
}

struct Ball restartBall(struct Ball b) {
    b.x = screenWidth / 2;
    b.y = screenHeight / 2 - 100;
    b.x_speed = ballDirection(-15, 15);
    b.y_speed = 10;
    return b;
}

int main() {
    InitWindow(screenWidth, screenHeight, title);
    struct Player player = {screenWidth / 2, screenHeight - 30, 100, 20, GRAY};
    struct Ball ball = {screenWidth / 2, screenHeight / 2, 14, RAYWHITE, 0, 10};
    ball.x_speed = ballDirection(-15, 15);

    // scoreboard
    int score = 0;
    int high_score = 0;

    // pieces
    int lines = 8;
    int line_pieces = 11;
    int piece_pos = 20;
    int line_pos = 30;
    Rect pieces[lines][line_pieces];
    updatePieces(lines, line_pieces, pieces, piece_pos, line_pos);

    BeginDrawing();
    EndDrawing();
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        SetTargetFPS(30);

        // scoreboard display
        DrawText(TextFormat("Score: %d", score), 10, 10, 20, WHITE);
        DrawText(TextFormat("High Score: %d", high_score), screenWidth - 240,
                 10, 20, WHITE);

        // player, ball and pieces display
        DrawRectangle(player.x, player.y, player.w, player.h, player.c);
        DrawCircle(ball.x, ball.y, ball.r, ball.c);
        for (int i = 0; i < lines; i++)
            for (int j = 0; j < line_pieces; j++)
                DrawRectangle(pieces[i][j].x, pieces[i][j].y,
                              pieces[i][j].width, pieces[i][j].height,
                              pieces[i][j].color);

        // movement
        if (player.x > 0 && IsKeyDown(KEY_A))
            player.x -= 20;
        else if (player.x <= screenWidth - 110 && IsKeyDown(KEY_D))
            player.x += 20;

        ball.x = ball.x + ball.x_speed;
        ball.y = ball.y + ball.y_speed;

        // collision
        if ((ball.x >= player.x && ball.x <= player.x + player.w) &&
            (ball.y >= player.y && ball.y <= player.y + player.h)) {
            ball.y_speed *= -1;
        }

        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < line_pieces; j++) {
                if ((ball.x >= pieces[i][j].x &&
                     ball.x <= pieces[i][j].x + pieces[i][j].width) &&
                    (ball.y >= pieces[i][j].y &&
                     ball.y <= pieces[i][j].y + pieces[i][j].height) &&
                    pieces[i][j].color.a != 0) {
                    ball.y_speed *= -1;
                    pieces[i][j].color = BLANK;
                    score += 100;
                    if (score > high_score)
                        high_score = score;
                }
            }
        }

        int max_score = 8800; // highest score is 8800
        if (ball.y > screenHeight || score == max_score) {
            score = 0;
            updatePieces(lines, line_pieces, pieces, piece_pos, line_pos);
            ball = restartBall(ball);
        } else if (ball.x < 0 || ball.x > screenWidth) {
            ball.x_speed *= -1;
        } else if (ball.y < 0) {
            ball.y_speed *= -1;
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
