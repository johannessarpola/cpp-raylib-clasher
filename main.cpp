#include <cstdio>
#include <stdlib.h>

#include "raylib.h"
#include "raymath.h"

class Character
{
public:
    Character(int fps, int frames, float scale, float speed);
    Vector2 get_world_pos() { return world_pos; }
    void init_screen_pos(int window_width, int window_height);
    void tick(float delta);
    void unload();
private:
    Texture2D texture{LoadTexture("assets/characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("assets/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("assets/characters/knight_run_spritesheet.png")};
    Vector2 screen_pos{};
    Vector2 world_pos{};
    
    float frame{};
    float running_time{};
    float update_time{1.f / 12.f}; // TODO Set with number of frames
    
    int total_frames{};
    float scale{4.f};
    float speed{4.f};
    float right_left{1.f};
};

void Character::unload() {
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}

Character::Character(int fps, int frames, float scale, float speed) {
    this->total_frames = frames;
    this->scale = scale;
    this->speed = speed;
    this->update_time = 1.f / (fps / frames);
}

void Character::init_screen_pos(int window_width, int window_height)
{
    screen_pos = {
        (float) window_width / 2.0f - scale * (0.5f * (float) texture.width / total_frames),
        (float) window_height / 2.0f - scale * (0.5f * (float) texture.height)};
}

void Character::tick(float delta)
{
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
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? right_left = -1.f : right_left = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    running_time += delta;
    if (running_time > update_time)
    {
        frame++;
        running_time = 0.f;
        if (frame > total_frames)
        {
            frame = 0;
        }
    }

    Rectangle src{
        (float) frame * (float) texture.width / (float) total_frames,
        0.f,
        (float) right_left * (float) texture.width / (float) total_frames,
        (float) texture.height};

    Rectangle dst{
        screen_pos.x,
        screen_pos.y,
        scale * (float) texture.width / (float) total_frames,
        scale * (float) texture.height};

    DrawTexturePro(texture, src, dst, Vector2{}, 0.f, WHITE);
}

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