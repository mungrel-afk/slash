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
        .position_vector = {screenWidth / 2, screenHeight / 2}, .width = 32, .height = 32, .speed = 128.0f, .health = 3};

    Entity enemy = {.position_vector = {100, 100}, .width = 32, .height = 64, .speed = 16.0f, .health = 1};

    //--------------------------------------------------------------------------------------
    //
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        float deltaTime = GetFrameTime();
        // Draw
        //----------------------------------------------------------------------------------
        //

        if (IsKeyDown(KEY_W))
        {
            player.position_vector.y -= player.speed * deltaTime;
        }
        if (IsKeyDown(KEY_A))
        {
            player.position_vector.x -= player.speed * deltaTime;
        }
        if (IsKeyDown(KEY_S))
        {
            player.position_vector.y += player.speed * deltaTime;
        }
        if (IsKeyDown(KEY_D))
        {
            player.position_vector.x += player.speed * deltaTime;
        }
        if(IsKeyDown(KEY_LEFT_SHIFT))
        {
            player.speed = 192;
        }else{
            player.speed = 128;
        }

        /* Attack */
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            // Get a vector from player to target enemy
            float player_to_enemy_distance = Vector2Distance(player.position_vector, enemy.position_vector);

            // check if the length to the target is less than the attack range

            // check if player is facing enemy direction

            // use half angle cosine to see if enemy is within attack cone
        }

        if (IsKeyPressed(KEY_R))
        {
            player.position_vector.x = screenWidth / 2;
            player.position_vector.y = screenHeight / 2;
            player.health--;
        }

        BeginDrawing();

        /* Draw Player Hearts */
        for (int i = 1; i <= player.health; i++)
        {
            DrawRectangle(i * 17, 10, 16, 16, RED);
        }

        /* Close game on player death */
        if (player.health <= 0)
        {
            EndDrawing();
            CloseWindow();
            return 0;
        }

        DrawRectangle(player.position_vector.x, player.position_vector.y, player.width, player.height, WHITE);
        DrawRectangle(enemy.position_vector.x, enemy.position_vector.y, enemy.width, enemy.height, BLUE);

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
