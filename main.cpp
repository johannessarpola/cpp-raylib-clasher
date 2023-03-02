#include <cstdio>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

class Character {
    public:
        Vector2 get_world_pos() { return world_pos; }

    private:
        Texture2D texture;
        Texture2D idle;
        Texture2D run;
        Vector2 screen_pos;
        Vector2 world_pos;
        float right_left{1.f};
        float current_frame{};
        float running_time{};
        float update_time{1.f/12.f};
};

int main()
{
    const int window_width = 384;
    const int window_height = 384;

    const int fps{60};

    InitWindow(window_width, window_height, "Clasher");
    SetTargetFPS(fps);

    Texture2D map = LoadTexture("assets/nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos = {};
    float speed{4.0};

    Texture2D knight{};
    Texture2D knight_run = LoadTexture("assets/characters/knight_run_spritesheet.png");
    Texture2D knight_idle = LoadTexture("assets/characters/knight_idle_spritesheet.png");
    const float knight_frames = 6.f;
    const float knight_scale = 4.0;
    Vector2 knight_pos{
        (float)window_width / 2.0f - knight_scale * (0.5f * (float)knight_run.width / knight_frames),
        (float)window_height / 2.0f - knight_scale * (0.5f * (float)knight_run.height)};

    // 1: face right, -1: facing left
    float right_left{1.f};
    // animation vars
    float knight_running_time{};
    float knight_current_frame{};
    const float knight_update_time{1.f / (fps / knight_frames)};

    float delta{};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        delta = GetFrameTime();

        Vector2 direction{};
        if (IsKeyDown(KEY_A))
            direction.x -= 1;
        if (IsKeyDown(KEY_D))
            direction.x += 1;
        if (IsKeyDown(KEY_W))
            direction.y -= 1;
        if (IsKeyDown(KEY_S))
            direction.y += 1;

        if (Vector2Length(direction) != 0.0)
        {
            map_pos = Vector2Subtract(map_pos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? right_left = -1.f : right_left = 1.f;
            knight = knight_run;
        } else {
            knight = knight_idle;
        }
        DrawTextureEx(map, map_pos, 0.0, 4.0, WHITE);

        knight_running_time += delta;
        if (knight_running_time > knight_update_time)
        {
            knight_current_frame++;
            knight_running_time = 0.f;
            if (knight_current_frame > knight_frames)
            {
                knight_current_frame = 0;
            }
        }

        Rectangle src{(float)knight_run.width / 6.f * knight_current_frame,
                      0.f,
                      right_left * (float)knight_run.width / 6.f,
                      (float)knight_run.height};

        Rectangle dst{
            knight_pos.x,
            knight_pos.y,
            knight_scale * knight_run.width / knight_frames,
            knight_scale * knight_run.height};
        
        DrawTexturePro(knight, src, dst, Vector2{}, 0.f, WHITE);
        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(knight_run);
    UnloadTexture(knight_idle);
}