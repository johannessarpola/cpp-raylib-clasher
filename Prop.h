#include "raylib.h"
#include "raymath.h"

class Prop 
{
public:
    Prop(Vector2 pos, Texture2D tex);
    void render(Vector2 player_pos);
    void unload() {
        UnloadTexture(texture);
    }
private:
    Texture2D texture{};
    Vector2 world_pos{};
    float scale{4.f};
};