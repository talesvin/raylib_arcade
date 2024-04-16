#include <raylib.h>

const int pongWidth = 1600;
const int pongHeight = 900;
const char *pongTitle = "Pong";

typedef struct PongPlayer {
    int posx;
    int posy;
    int width;
    int height;
} PongPlayer;

typedef struct PongBall {
    int radius;
    int posx;
    int posy;
    int x_speed;
    int y_speed;
} PongBall;

int ballSpeed(int min, int max, bool spd) {
    int value = GetRandomValue(min, max);
    if (spd == false) {
        return value;
    } else {
        while (value * -1 <= 4)
            value = GetRandomValue(min, max);
        return value;
    }
}

PongBall updatePongBall() {
    PongBall ball = {14, pongWidth / 2, pongHeight / 2, ballSpeed(-8, 8, true),
                     ballSpeed(-8, 8, false)};
    return ball;
}

void pong() {
    InitWindow(pongWidth, pongHeight, pongTitle);

    PongPlayer player1 = {5, pongHeight / 2, 20, 100};
    PongPlayer player2 = {pongWidth - 25, pongHeight / 2, 20, 100};

    PongBall ball = updatePongBall();
    int left = 0;
    int right = 0;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        SetTargetFPS(30);

        DrawLine(pongWidth / 2, 0, pongWidth / 2, pongHeight, GRAY);
        DrawRectangle(player1.posx, player1.posy, player1.width, player1.height,
                      WHITE);
        DrawRectangle(player2.posx, player2.posy, player2.width, player2.height,
                      WHITE);
        DrawCircle(ball.posx, ball.posy, ball.radius, WHITE);

        // scoreboard
        DrawText(TextFormat("%d", left), 100, 10, 30, WHITE);
        DrawText(TextFormat("%d", right), pongWidth - 100, 10, 30, WHITE);

        // controls
        // player1
        if (IsKeyDown(KEY_W) && player1.posy > 0) {
            player1.posy -= 10;
        } else if (IsKeyDown(KEY_S) &&
                   player1.posy + player1.height < pongHeight) {
            player1.posy += 10;
        }

        // player2
        if (IsKeyDown(KEY_UP) && player2.posy > 0) {
            player2.posy -= 10;
        } else if (IsKeyDown(KEY_DOWN) &&
                   player2.posy + player2.height < pongHeight) {
            player2.posy += 10;
        }

        // ball
        ball.posx = ball.posx + ball.x_speed;
        ball.posy = ball.posy + ball.y_speed;
        if (ball.posy - ball.radius < 0 ||
            ball.posy + ball.radius > pongHeight) {
            ball.y_speed *= -1;
        }

        // detect paddle collision
        int ball_paddle_diff1 = player1.width + ball.radius;
        int ball_paddle_diff2 = player1.width - ball.radius;
        int paddle_height1 = ball.posy >= player1.posy &&
                             ball.posy <= player1.posy + player1.height;
        int paddle_height2 = ball.posy >= player2.posy &&
                             ball.posy <= player2.posy + player2.height;

        // collision left paddle
        if (ball.x_speed <= 0 &&
            (ball.posx - (ball_paddle_diff1) <= player1.posx) &&
            paddle_height1) {
            ball.x_speed *= -1;  // revert the ball direction
            ball.x_speed *= 1.5; // increase the ball speed
        }

        // collision right paddle
        if (ball.x_speed >= 0 &&
            (ball.posx + (ball_paddle_diff2) >= player2.posx) &&
            paddle_height2) {
            ball.x_speed *= 1.5;
            ball.x_speed *= -1;
        }

        // reset ball and update scoreboard
        if (ball.posx < 0) {
            ball = updatePongBall();
            right++;
        } else if (ball.posx > pongWidth) {
            ball = updatePongBall();
            left++;
        }
        EndDrawing();
    }
    CloseWindow();
}
