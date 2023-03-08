#include "Enemy.h"

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
    world_pos_previous = world_pos;
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
        static_cast<float>(frame) * width,
        0.f,
        static_cast<float>(right_left) * width,
        height};

    Rectangle dst{
        screen_pos.x,
        screen_pos.y,
        scale * width,
        scale * height};

    DrawTexturePro(texture, src, dst, Vector2{}, 0.f, WHITE);
}


