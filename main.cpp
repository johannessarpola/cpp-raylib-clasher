#include <cstdio>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"

int main()
{
    const int window_width = 384;
    const int window_height = 384;

    const int fps{60};

    InitWindow(window_width, window_height, "Clasher");
    SetTargetFPS(fps);

    Texture2D map = LoadTexture("assets/nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos{0.f, 0.f};
    Character knight(
        Vector2{0.f, 0.f},
        LoadTexture("assets/characters/knight_idle_spritesheet.png"),
        LoadTexture("assets/characters/knight_run_spritesheet.png"),
        fps, 
        6, 
        4.f, 
        4.f);

    knight.set_screen_pos(window_width, window_height);

    Prop props[2]
    {
        Prop{Vector2{600.f, 300.f}, LoadTexture("assets/nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("assets/nature_tileset/Log.png")}
    };
    Enemy goblin{
        Vector2{100.f, 100.f},
        LoadTexture("assets/characters/goblin_idle_spritesheet.png"),
        LoadTexture("assets/characters/goblin_run_spritesheet.png")
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
        goblin.tick(delta);

        EndDrawing();
    }

    UnloadTexture(map);
    knight.unload();
    goblin.unload();
    for (auto prop : props)
    {
        prop.unload();
    }
}