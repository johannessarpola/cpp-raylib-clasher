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
    set_dims();
}

void Enemy::tick(float delta)
{
    screen_pos = Vector2Subtract(world_pos, target->get_world_pos());
    BaseCharacter::tick(delta);
}
