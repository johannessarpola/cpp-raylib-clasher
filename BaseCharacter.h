#include "raylib.h"

#ifndef BASE_CHARACTER_H // lol @ cpp
#define BASE_CHARACTER_H // lol @ cpp

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 get_world_pos() { return world_pos; }
    void undo_movement();
    void unload();
    Rectangle get_collision_rec();
protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 screen_pos{};
    Vector2 world_pos{};
    Vector2 world_pos_previous{};

    float frame{};
    float running_time{};
    float update_time{1.f / 12.f};
    
    int total_frames{6};
    float scale{4.f};
    float speed{4.f};
    float right_left{1.f};

    float width{};
    float height{};
    void set_dims();
private:

};

#endif