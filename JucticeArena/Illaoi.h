#pragma once
#include "MeleeHero.h"
#include "IllaoiDefines.h"

struct Illaoi : public MeleeHero
{
    Illaoi(const Rect& r, Direction dir = UP, State state = IDLE)
        : MeleeHero(r, Texture("illaoi.png", Point(), COUNT_OF_FRAMES, COUNT_OF_FRAMES),
        Texture("shen_attack.png", Point(), COUNT_OF_FRAMES_AA, COUNT_OF_FRAMES), "illaoi",
        IL_MOVE_SPEED, IL_HEALTH, IL_DAMAGE, IL_RANGE, IL_AUTOATTACK_SPEED,
        IL_SPEC1_COOLDOWN, IL_SPEC2_COOLDOWN, SoundEffect("melee_attack.wav"), dir, state)
    {
        max_health = IL_HEALTH;
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

    virtual ~Illaoi() {}

    virtual void draw() //  if state == ATTACK he will end his attack animation 
    {
        if (state == ATTACK)
        {
            al_draw_bitmap_region(autoattack_animation.texture, autoattack_animation.frame.p.x, autoattack_animation.frame.p.y,
                autoattack_animation.frame.w, autoattack_animation.frame.h, boundary.p.x, boundary.p.y, NULL);

            autoattack_animation.frame.p.x += autoattack_animation.frame.w;
            if (autoattack_animation.frame.p.x >= COUNT_OF_FRAMES_AA * autoattack_animation.frame.w)
            {
                state = IDLE;
            }
            return;
        }
        else if (state == IDLE)
        {
            texture.frame.p.x = 0;
        }
        al_draw_bitmap_region(texture.texture, texture.frame.p.x, texture.frame.p.y,
            texture.frame.w, texture.frame.h, boundary.p.x, boundary.p.y, NULL);

        if (autoattack_state != 0)
            --autoattack_state;
        if (spec1_state != 0)
            --spec1_state;
        if (spec2_state != 0)
            --spec2_state;
        if (frozen > 0)
            --frozen;
        else if (frozen < 0)
            ++frozen;
        draw_life_bar();
    }
    virtual void move(const Direction dir_)
    {
        if (frozen <= 0)
        {
            if (state == ATTACK)
            {
                return;
            }

            if (dir != dir_)
            {
                dir = dir_;
                texture.frame.p.x = texture.frame.w;
                texture.frame.p.y = dir * texture.frame.h;
                state = MOVE;
                return;
            }

            texture.frame.p.x += texture.frame.w;
            if (texture.frame.p.x >= COUNT_OF_FRAMES * texture.frame.w)
            {
                texture.frame.p.x = texture.frame.w;
            }

            state = MOVE;
            for (int i = move_speed; i >= 1; --i)
            {
                std::pair<int, int> c = move_coords(dir, i);
                Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), boundary.w, boundary.h);

                if (!hit_wall(r) && !hit_water(r) && in_range(r))
                {
                    boundary = r;
                    break;
                }
            }
        }
    }
    virtual Ability spec1(Hero& h)
    {
        if (frozen <= 0 && spec1_state == 0)
        {
            if (is_able_to_attack(h))
            {
                h.frozen = IL_FROZE_TIME;
                h.health -= 100;
                autoattack(h);
            }
        }

        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual Ability spec1(Hero& h1, Hero& h2)
    {
        if (frozen <= 0 && spec1_state == 0)
        {
            if (is_able_to_attack(h1))
            {
                h1.frozen = IL_FROZE_TIME;
                h1.health -= 100;
                autoattack(h1);
            }
            else if (is_able_to_attack(h2))
            {
                h2.frozen = IL_FROZE_TIME;
                h2.health -= 100;
                autoattack(h2);
            }
        }

        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual Ability spec2(Hero& h1, Hero& h2)
    {
        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual Ability spec2(Hero& h)
    {
        std::pair<int, int> c = move_coords(dir, 150);
        int x = boundary.p.x + c.first;
        int y = boundary.p.y + c.second;
        Rect r = Rect(Point(x, y), boundary.w, boundary.h);
        if (h.boundary.intersects_rect(r))
        {
            extra = 5;
            h.frozen = 5;
            
            state = ATTACK;
            autoattack_animation.frame.p.x = 0;
            autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;
        }

        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual void passive(Hero& h)
    {
        if (extra <= 5 && extra > 1)
        {
            if (dir == LEFT)
            {
                ALLEGRO_BITMAP* tent = al_load_bitmap("illaoi_tentacle_left.png");
                al_draw_bitmap(tent, boundary.p.x + 50, boundary.p.y, NULL);
            }
            else if (dir == RIGHT)
            {
                ALLEGRO_BITMAP* tent = al_load_bitmap("illaoi_tentacle_right.png");
                al_draw_bitmap(tent, boundary.p.x - 50, boundary.p.y, NULL);
            }
            else if (dir == DOWN)
            {
                ALLEGRO_BITMAP* tent = al_load_bitmap("illaoi_tentacle_down.png");
                al_draw_bitmap(tent, boundary.p.x, boundary.p.y + 50, NULL);
            }
            else if (dir == UP)
            {
                ALLEGRO_BITMAP* tent = al_load_bitmap("illaoi_tentacle_up.png");
                al_draw_bitmap(tent, boundary.p.x, boundary.p.y - 50, NULL);
            }
            --extra;
        }
        else if (extra == 1)
        {
            h.boundary.p.x = boundary.p.x;
            h.boundary.p.y = boundary.p.y;
            std::pair<int, int> c = move_coords(dir, 50);
            h.boundary.p.x += c.first;
            h.boundary.p.y += c.second;
            extra = 0;
        }
    }
    virtual void passive(Hero& h1, Hero& h2) {}
};