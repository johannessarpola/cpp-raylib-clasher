#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
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
      virtual void tick(float delta) override;
      void set_Target(Character *target) { this->target = target; }
      virtual Vector2 get_screen_pos() override;

private:
      Character *target{};
      float damage_per_second{10.f};
};