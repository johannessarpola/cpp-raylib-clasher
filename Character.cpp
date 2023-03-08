#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character(Vector2 pos,
                     Texture2D idle,
                     Texture run,
                     int window_width,
                     int window_height)
{
    texture = idle;
    idle = idle;
    run = run;
    world_pos = pos;
    set_dims();
    set_screen_pos(window_width, window_height);
}

Character::Character(Vector2 pos,
                     Texture2D idle,
                     Texture run,
                     int fps,
                     int frames,
                     float scale,
                     float speed,
                     int window_width,
                     int window_height)
{
    this->texture = idle;
    this->idle = idle;
    this->run = run;
    world_pos = pos;
    this->total_frames = frames;
    this->scale = scale;
    this->speed = speed;
    this->update_time = 1.f / (static_cast<float>(fps) / static_cast<float>(frames));
    set_dims();
    set_screen_pos(window_width, window_height);
}

void Character::set_screen_pos(int window_width, int window_height)
{
    this->screen_pos = {
        static_cast<float>(window_width) / 2.0f - scale * (0.5f * width / total_frames),
        static_cast<float>(window_height) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float delta)
{
    BaseCharacter::tick(delta);
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
}