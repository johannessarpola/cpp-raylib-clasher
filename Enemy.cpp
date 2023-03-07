#include "Enemy.h"

Enemy::Enemy(Vector2 pos,
             Texture2D idle,
             Texture run) :
    texture(idle),
    idle(idle),
    run(run),
    world_pos(pos)
{
    set_dims();
}
Enemy::Enemy(Vector2 pos,
             Texture2D idle,
             Texture run,
             int fps,
             int frames,
             float scale,
             float speed) :
    texture(idle),
    idle(idle),
    run(run),
    world_pos(pos)
{
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

Rectangle Enemy::get_collision_rec() 
{    
    return Rectangle{
        screen_pos.x,
        screen_pos.y,
        width * scale,
        height * scale
    };
}

void Enemy::undo_movement() {
    world_pos = world_pos_previous;
}

void Enemy::set_dims() {
    this->height = static_cast<float>(texture.height);
    this->width = static_cast<float>(texture.width) / static_cast<float>(total_frames);
}

void Enemy::unload() {
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}