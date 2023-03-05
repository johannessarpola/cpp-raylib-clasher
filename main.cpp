#include <cstdio>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
    const int window_width = 384;
    const int window_height = 384;

    const int fps{60};

    InitWindow(window_width, window_height, "Clasher");
    SetTargetFPS(fps);

    Texture2D map = LoadTexture("assets/nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos{0.f, 0.f};    
    Character knight(fps, 6, 4.f, 4.f);
    knight.init_screen_pos(window_width, window_height);

    float delta{};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        delta = GetFrameTime();
        DrawTextureEx(map, map_pos, 0.0, 4.0, WHITE);

        knight.tick(delta);
        map_pos = Vector2Scale(knight.get_world_pos(), -1.f);
        EndDrawing();
    }

    UnloadTexture(map);
    knight.unload();
}