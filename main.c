#include <raylib.h>
#include <raymath.h>

#define MAX_BALL_COUNT 10


typedef struct {

    Vector2 ballPos;
    Vector2 ballSpeed;
    int ballRadius;
    int balls_product;
    Color color;
    float massive;

} Ball;

int main(void) {


    SetConfigFlags(FLAG_MSAA_4X_HINT); //bu bir kenar basina 4 ornekleme yapan bir anti-alliasing cagrisidir. (kenar yumusatma)
    const int screenWidth = 800;
    const int screenHeight = 450;


    Color colors[] = {RED, BLUE, GREEN};

    InitWindow(screenWidth, screenHeight, "bouncing");

    Ball balls[MAX_BALL_COUNT] = {0};

    int ball_counter = 0;

    bool pause = false;
    int framesCounter = 0;

    SetTargetFPS(60);


    while(!WindowShouldClose()) {

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {

            
            if (ball_counter > MAX_BALL_COUNT) ball_counter = 0;
            ball_counter++;
            balls[ball_counter].ballPos = (Vector2){GetRandomValue(200,screenWidth-200),GetRandomValue(50,screenHeight-50)};
            balls[ball_counter].ballSpeed = (Vector2){(float)GetRandomValue(10,50)/10.0f,(float)GetRandomValue(10,50)/10.0f};
            balls[ball_counter].ballRadius = GetRandomValue(10,24);
            balls[ball_counter].color = colors[GetRandomValue(0,2)];
            balls[ball_counter].massive = (float)balls[ball_counter].ballRadius/10.f;
        }

        if (IsKeyPressed(KEY_SPACE)) pause = !pause;

        if (!pause) {

            for (int i=1;i <=ball_counter; ++i) {
                balls[i].ballPos.x += balls[i].ballSpeed.x;
                balls[i].ballPos.y += balls[i].ballSpeed.y;

                if ((balls[i].ballPos.x >= (GetScreenWidth() - balls[i].ballRadius)) || (balls[i].ballPos.x <= balls[i].ballRadius)) balls[i].ballSpeed.x *= -1.0f;
                if ((balls[i].ballPos.y >= (GetScreenHeight() - balls[i].ballRadius)) || (balls[i].ballPos.y <= balls[i].ballRadius)) balls[i].ballSpeed.y *= -1.0f;
            }

            
        }

        else framesCounter++;


        //DRAW
        BeginDrawing();

            ClearBackground(RAYWHITE);
            for (int i=1;i<=ball_counter;++i) DrawCircleV(balls[i].ballPos, (float)balls[i].ballRadius, balls[i].color);
            if (pause) {
                DrawText("PAUSED", 350, 200, 30, GRAY);
                for (int i=1;i<=ball_counter;i++) {
                    float magnitude = Vector2Length(balls[i].ballSpeed);
                    DrawText(TextFormat("p = %.2f * %.2f", balls[i].massive, magnitude)
                    , balls[i].ballPos.x-10, balls[i].ballPos.y - (balls[i].ballRadius + 10), 20, BLACK);
                     DrawText(TextFormat("v_x = %.2f, v_y =  %.2f",balls[i].ballSpeed.x, balls[i].ballSpeed.y)
                    , balls[i].ballPos.x-10, balls[i].ballPos.y - (balls[i].ballRadius -5), 20, GRAY);
                }

            }
            DrawFPS(10, 10);

        EndDrawing();

    }

    CloseWindow();
    return 0;
}