#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <cstdint>
#include <cstdio>
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
    Vector2 direction_vector;
    int width;
    int height;
    float speed;
    int health;
    int attack_range = 128;
    float attack_arc = 120.00; // 120deg arc from the
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
    Entity player = {.position_vector = {screenWidth / 2, screenHeight / 2},
                     .width = 32,
                     .height = 32,
                     .speed = 128.0f,
                     .health = 3};

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

        /* Attack
         * The main idea for an Attack is that the player creates a hitbox in the direction they're facing then when
         * that hitbox overlaps with the enemies hurtbox it substracts some amount of health */
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
        {
            Vector2 facing_vector = Vector2Subtract(GetMousePosition(), player.position_vector);

            Vector2 player_center = {player.position_vector.x + player.width / 2,
                                     player.position_vector.y + player.height / 2};

            player.direction_vector = Vector2Normalize(facing_vector);

            float angle = atan2(player.direction_vector.y, player.direction_vector.x);

            Vector2 hitbox_vector = {player_center.x + (player.direction_vector.x * player.attack_range),
                                     player_center.y + (player.direction_vector.y * player.attack_range)};

            DrawLine(player_center.x, player_center.y, hitbox_vector.x, hitbox_vector.y, WHITE);
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
