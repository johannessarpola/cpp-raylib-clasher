#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
    Character(Vector2 pos,
          Texture2D idle,
          Texture run);
    Character(Vector2 pos,
          Texture2D idle,
          Texture run,
          int fps, 
          int frames, 
          float scale, 
          float speed);
    virtual void tick(float delta) override;
    void set_screen_pos(int window_width, int window_height);
};