#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::tick(float delta)
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

Rectangle BaseCharacter::get_collision_rec() 
{    
    return Rectangle{
        screen_pos.x,
        screen_pos.y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::undo_movement() 
{
    world_pos = world_pos_previous;
}

void BaseCharacter::set_dims() 
{
    this->height = static_cast<float>(texture.height);
    this->width = static_cast<float>(texture.width) / static_cast<float>(total_frames);
}

void BaseCharacter::unload() 
{
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}