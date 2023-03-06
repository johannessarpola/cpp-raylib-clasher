#include "raylib.h"

class Character
{
public:
    Character(int window_width, int window_height);
    Character(int fps, int frames, float scale, float speed, int window_width, int window_height);
    Vector2 get_world_pos() { return world_pos; }
    void tick(float delta);
    void undo_movement();
    void unload();
private:
    Texture2D texture{LoadTexture("assets/characters/knight_idle_spritesheet.png")};
    Texture2D idle{LoadTexture("assets/characters/knight_idle_spritesheet.png")};
    Texture2D run{LoadTexture("assets/characters/knight_run_spritesheet.png")};
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
    void set_screen_pos(int window_width, int window_height);
    void set_dims();
};