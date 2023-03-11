#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos,
             Texture2D idle,
             Texture run)
{
    this->texture = idle;
    this->idle = idle;
    this->run = run;
    this->world_pos = pos;
    this->speed = 3.f;
    this->set_dims();
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
    this->world_pos = pos;
    this->total_frames = frames;
    this->scale = scale;
    this->speed = speed;
    this->update_time = 1.f / (static_cast<float>(fps) / static_cast<float>(frames));
    this->speed = 3.f;
    this->set_dims();
}

Vector2 Enemy::get_screen_pos() 
{
    return Vector2Subtract(world_pos, target->get_world_pos());
}

void Enemy::tick(float delta)
{
    if(!is_alive()) return;
    velocity = Vector2Subtract(target->get_screen_pos(), this->get_screen_pos());
    BaseCharacter::tick(delta);
}
