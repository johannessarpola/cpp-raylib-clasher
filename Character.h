#include "raylib.h"
#include "BaseCharacter.h"

#ifndef CHARACTER_H // lol @ cpp
#define CHARACTER_H // lol @ cpp

class Character : public BaseCharacter
{
public:
      Character(Vector2 pos,
                Texture2D idle,
                Texture run,
                int window_width,
                int window_height);
      Character(Vector2 pos,
                Texture2D idle,
                Texture run,
                int fps,
                int frames,
                float scale,
                float speed,
                int window_width,
                int window_height);
      virtual void tick(float delta) override;
      virtual Vector2 get_screen_pos() override;
      virtual void unload() override;
      Rectangle get_Weapon_collision_rec() { return weapon_collision_rec; }
      bool get_health() const { return health; }
      void take_damage(float damage);

private:
      Texture2D weapon{LoadTexture("assets/characters/weapon_sword.png")};
      void set_screen_pos(int window_width, int window_height);
      int window_width{};
      int window_height{};
      Rectangle weapon_collision_rec{};
      float health{100.f};

      
};

#endif