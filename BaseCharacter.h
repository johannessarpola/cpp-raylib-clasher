#include "raylib.h"

#ifndef BASE_CHARACTER_H // lol @ cpp
#define BASE_CHARACTER_H // lol @ cpp

class BaseCharacter
{
public:
    BaseCharacter();
    Vector2 get_world_pos() { return world_pos; }
    void undo_movement();
    virtual void unload();
    Rectangle get_collision_rec();
    virtual void tick(float delta);
    virtual Vector2 get_screen_pos() = 0; // HOX: pure virtual function -> abstract class
    bool is_alive(){ return alive; };
    bool set_alive(bool alive) { this->alive = alive; }
protected:
    Texture2D texture{};
    Texture2D idle{};
    Texture2D run{};
    Vector2 world_pos{};
    Vector2 world_pos_previous{};
    Vector2 velocity{};

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
    bool alive{true};

};

#endif