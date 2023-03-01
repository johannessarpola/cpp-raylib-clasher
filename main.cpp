#include <cstdio>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

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

    Texture2D knight = LoadTexture("assets/characters/knight_idle_spritesheet.png");
    const float knight_frames = 6.f;
    const float knight_scale = 4.0;
    Vector2 knight_pos{
        (float) window_width / 2.0f - knight_scale * (0.5f * (float) knight.width / knight_frames),
        (float) window_height / 2.0f - knight_scale * (0.5f * (float) knight.height)};

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        float delta = GetFrameTime();

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
        }
        DrawTextureEx(map, map_pos, 0.0, 4.0, WHITE);
        Rectangle src{0.f, 0.f , (float) knight.width/6.f, (float) knight.height};
        Rectangle dst{knight_pos.x, knight_pos.y, knight_scale * knight.width/knight_frames, knight_scale * knight.height};
        DrawTexturePro(knight, src, dst, Vector2{}, 0.f, WHITE);
        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(knight);
}