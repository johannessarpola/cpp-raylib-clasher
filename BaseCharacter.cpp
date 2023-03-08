#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

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

void BaseCharacter::undo_movement() {
    world_pos = world_pos_previous;
}

void BaseCharacter::set_dims() {
    this->height = static_cast<float>(texture.height);
    this->width = static_cast<float>(texture.width) / static_cast<float>(total_frames);
}

void BaseCharacter::unload() {
    UnloadTexture(texture);
    UnloadTexture(idle);
    UnloadTexture(run);
}