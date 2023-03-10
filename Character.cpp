#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character(Vector2 pos,
                     Texture2D idle,
                     Texture run,
                     int window_width,
                     int window_height)
{
    this->texture = idle;
    this->idle = idle;
    this->run = run;
    this->world_pos = pos;
    set_dims();
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
    this->world_pos = pos;
    this->total_frames = frames;
    this->scale = scale;
    this->speed = speed;
    this->update_time = 1.f / (static_cast<float>(fps) / static_cast<float>(frames));
    this->window_width = window_width;
    this->window_height = window_height;
    set_dims();
}

Vector2 Character::get_screen_pos()
{
    return Vector2{
        static_cast<float>(window_width) / 2.0f - scale * (0.5f * width / total_frames),
        static_cast<float>(window_height) / 2.0f - scale * (0.5f * height)};
}

void Character::tick(float delta)
{
    if (IsKeyDown(KEY_A))
        velocity.x -= 1;
    if (IsKeyDown(KEY_D))
        velocity.x += 1;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1;
    if (IsKeyDown(KEY_S))
        velocity.y += 1;

    BaseCharacter::tick(delta);
}