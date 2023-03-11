#include "Character.h"
#include "raylib.h"
#include "raymath.h"

Character::Character(Vector2 pos,
                     Texture2D idle,
                     Texture run,
                     int window_width,
                     int window_height)
{
    this->texture = idle;
    this->idle = idle;
    this->run = run;
    this->world_pos = pos;
    set_dims();
}

Character::Character(Vector2 pos,
                     Texture2D idle,
                     Texture run,
                     int fps,
                     int frames,
                     float scale,
                     float speed,
                     int window_width,
                     int window_height)
{
    this->texture = idle;
    this->idle = idle;
    this->run = run;
    this->world_pos = pos;
    this->total_frames = frames;
    this->scale = scale;
    this->speed = speed;
    this->update_time = 1.f / (static_cast<float>(fps) / static_cast<float>(frames));
    this->window_width = window_width;
    this->window_height = window_height;
    set_dims();
}

Vector2 Character::get_screen_pos()
{
    return Vector2{
        static_cast<float>(window_width) / 2.0f - scale * (0.5f * width / total_frames),
        static_cast<float>(window_height) / 2.0f - scale * (0.5f * height)};
}

void Character::unload()
{
    BaseCharacter::unload();
    UnloadTexture(weapon);
}

void Character::take_damage(float damage) {
    health -= damage;
    if(health <= 0.f) {
        set_alive(false);
    }
}

void Character::tick(float delta)
{
    if(!is_alive()) return;
    if (IsKeyDown(KEY_A))
        velocity.x -= 1;
    if (IsKeyDown(KEY_D))
        velocity.x += 1;
    if (IsKeyDown(KEY_W))
        velocity.y -= 1;
    if (IsKeyDown(KEY_S))
        velocity.y += 1;

    BaseCharacter::tick(delta);

    Vector2 origin{};
    Vector2 offset{};
    Vector2 screen_pos = get_screen_pos();
    float rotation;
    if (right_left > 0.f)
    {
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f}; // magic numbers ftw
        weapon_collision_rec = {
            screen_pos.x + offset.x,
            screen_pos.y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? 35.f : 0.f;
    }
    else
    {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f}; // magic numbers ftw
        weapon_collision_rec = {
            screen_pos.x + offset.x - weapon.width * scale,
            screen_pos.y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale};

        rotation = IsMouseButtonDown(MOUSE_LEFT_BUTTON) ? -35.f : 0.f;            
    }

    Rectangle src{0.f, 0.f, static_cast<float>(weapon.width) * right_left, static_cast<float>(weapon.height)};
    Rectangle dst{screen_pos.x + offset.x, screen_pos.y + offset.y, weapon.width * scale, weapon.height * scale};
    DrawTexturePro(weapon, src, dst, origin, rotation, WHITE);
    DrawRectangleLines(
        weapon_collision_rec.x,
        weapon_collision_rec.y,
        weapon_collision_rec.width,
        weapon_collision_rec.height, 
        RED);
}