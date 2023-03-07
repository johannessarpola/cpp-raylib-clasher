#include "Prop.h"

Prop::Prop(Vector2 pos, Texture2D tex) : 
    // lol @ c++
    world_pos(pos),
    texture(tex)
{

}
// scope resolution operator
void Prop::render(Vector2 player_pos) 
{
    Vector2 screen_pos{Vector2Subtract(world_pos, player_pos)};
    DrawTextureEx(texture, screen_pos, 0.f, scale, WHITE);
}

Rectangle Prop::get_collision_rec(Vector2 player_pos) 
{
    Vector2 screen_pos{Vector2Subtract(world_pos, player_pos)};
    return Rectangle {
        screen_pos.x,
        screen_pos.y,
        texture.width * scale,
        texture.height * scale
    };
}
