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

private:
      Character *target{};
};