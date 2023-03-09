#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos,
             Texture2D idle,
             Texture run)
{
    texture = idle;
    idle = idle;
    run = run;
    world_pos = pos;
    this->speed = 3.f;
    set_dims();
}

Enemy::Enemy(Vector2 pos,
             Texture2D idle,
             Texture run,
             int fps,
             int frames,
             float scale,
             float speed)
{
    this->texture = idle;
    this->idle = idle;
    this->run = run;
    world_pos = pos;
    this->total_frames = frames;
    this->scale = scale;
    this->speed = speed;
    this->update_time = 1.f / (static_cast<float>(fps) / static_cast<float>(frames));
    this->speed = 3.f;
    set_dims();
}

void Enemy::tick(float delta)
{
    screen_pos = Vector2Subtract(world_pos, target->get_world_pos());
    // vec to target
    Vector2 to_target = Vector2Subtract(target->get_screen_pos(), screen_pos);
    // normalize vec
    to_target = Vector2Normalize(to_target);
    // multiply by actor speed
    to_target = Vector2Scale(to_target, speed);
    // move actor
    world_pos = Vector2Add(world_pos, to_target);

    BaseCharacter::tick(delta);
}
