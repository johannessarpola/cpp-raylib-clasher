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