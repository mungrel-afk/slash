#include "raylib.h"
#include "raymath.h"
#include <cstdint>
using namespace std;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

struct Entity
{
    Vector2 position_vector;
    int width;
    int height;
    float speed;
    int health;
};

struct game_state
{
};

float Interpolate(float goal, float current, float interpolant)
{
    float difference = goal - current;
    if (difference > interpolant) return current + interpolant;
    if (difference < -interpolant) return current - interpolant;
    return goal;
}

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const u16 screenWidth = 1366;
    const u16 screenHeight = 768;
    InitWindow(screenWidth, screenHeight, "Slash");
    int targetFPS = 144;
    SetTargetFPS(targetFPS);

    /* Player Stuff */
    Entity player = {
        .position_vector = {screenWidth / 2, screenHeight / 2}, .width = 32, .height = 32, .speed = 32.0f, .health = 3};

    //--------------------------------------------------------------------------------------
    //
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();
        // Draw
        //----------------------------------------------------------------------------------
        //
        DrawRectangle(player.position_vector.x, player.position_vector.y, player.width, player.height, WHITE);

        if (IsKeyDown(KEY_W))
        {
            player.position_vector.y -= player.speed;
        }
        if (IsKeyDown(KEY_A))
        {
            player.position_vector.x -= player.speed;
        }
        if (IsKeyDown(KEY_S))
        {
            player.position_vector.y += player.speed;
        }
        if (IsKeyDown(KEY_D))
        {
            player.position_vector.x += player.speed;
        }

        if (IsKeyPressed(KEY_R))
        {
            player.position_vector.x = screenWidth / 2;
            player.position_vector.y = screenHeight / 2;
        }

        /* Draw Player Hearts */
        for (int i = 1; i <= player.health; i++)
        {
            DrawRectangle(i*17, 10, 16, 16, RED);
        }

        BeginDrawing();
        ClearBackground(BLACK);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
