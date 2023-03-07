#include <cstdio>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"

int main()
{
    const int window_width = 384;
    const int window_height = 384;

    const int fps{60};

    InitWindow(window_width, window_height, "Clasher");
    SetTargetFPS(fps);

    Texture2D map = LoadTexture("assets/nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos{0.f, 0.f};
    Character knight(fps, 6, 4.f, 4.f, window_width, window_height);

    Prop props[2]
    {
        Prop{Vector2{600.f, 300.f}, LoadTexture("assets/nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("assets/nature_tileset/Log.png")}
    };

    float map_scale = 4.;
    float delta{};
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);
        delta = GetFrameTime();

        map_pos = Vector2Scale(knight.get_world_pos(), -1.f);
        DrawTextureEx(map, map_pos, 0.0, map_scale, WHITE);

        for (auto prop : props)
        {
            prop.render(knight.get_world_pos());
        }

        knight.tick(delta);
        // check maps bounds
        if (knight.get_world_pos().x < 0.f ||
            knight.get_world_pos().y < 0.f ||
            knight.get_world_pos().x + window_width > map.width * map_scale ||
            knight.get_world_pos().y + window_height > map.height * map_scale)
        {
            knight.undo_movement();
        }
        for (auto prop : props)
        {
            Rectangle prop_rec = prop.get_collision_rec(knight.get_world_pos());
            Rectangle plr_rec = knight.get_collision_rec();
            if(CheckCollisionRecs(prop_rec, plr_rec)) {
                knight.undo_movement();
            }
        }


        EndDrawing();
    }

    UnloadTexture(map);
    knight.unload();
    for (auto prop : props)
    {
        prop.unload();
    }
}