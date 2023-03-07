#include "raylib.h"

class Enemy
{
public:
    Enemy(Vector2 pos,
          Texture2D idle,
          Texture run);
    Enemy(Vector2 pos,
          Texture2D idle,
          Texture run,
          int fps, 
          int frames, 
          float scale, 
          float speed);
    Vector2 get_world_pos() {
        return world_pos; }
    void tick(float delta);
    void undo_movement();
    void unload();
    Rectangle get_collision_rec();

private:
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
};