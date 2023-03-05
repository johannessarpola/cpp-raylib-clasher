#include "Character.h"
#include "raylib.h"
#include "raymath.h"

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
    this->height = (float) texture.height;
    this->width = (float) texture.width / (float) frames;
}

void Character::init_screen_pos(int window_width, int window_height)
{
    screen_pos = {
        (float) window_width / 2.0f - scale * (0.5f * width / total_frames),
        (float) window_height / 2.0f - scale * (0.5f * height)};
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
        (float) frame * width,
        0.f,
        (float) right_left * width,
        height};

    Rectangle dst{
        screen_pos.x,
        screen_pos.y,
        scale * width,
        scale * height};

    DrawTexturePro(texture, src, dst, Vector2{}, 0.f, WHITE);
}