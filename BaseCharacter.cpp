#include "BaseCharacter.h"
#include "raymath.h"

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

    if (Vector2Length(velocity) != 0.0)
    {
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? right_left = -1.f : right_left = 1.f;
        texture = run;
    }
    else
    {
        texture = idle;
    }

    velocity = {};
    
    Vector2 screen_pos = get_screen_pos();

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
    Vector2 screen_pos = get_screen_pos();
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