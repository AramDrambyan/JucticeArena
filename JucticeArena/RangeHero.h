#pragma once
#include "Hero.h"

struct RangeHero : public Hero
{
    virtual ~RangeHero() {}

    int range;

    RangeHero(const Rect& r, const Texture& texture, const Texture& autoattack_animation,
        int move_speed, int health, int damage, int range, int autoattack_speed, Direction dir = DOWN, State state = IDLE)
        : Hero(r, texture, autoattack_animation, move_speed, health, damage, autoattack_speed, dir, state), range(range) {}

    virtual bool is_able_to_attack(const Hero& h)
    {
        std::pair<int, int> c = move_coords(dir, range);
        Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), boundary.w, boundary.h);

        if (r.intersects_rect(h.boundary))
            return true;
        return false;
    }
    virtual void autoattack(Hero& h)
    {
        state = ATTACK;
        h.health -= damage;

        autoattack_state = autoattack_speed;
        autoattack_animation.frame.p.x = 0;
        autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;
    }
    virtual void draw() //  if state == ATTACK he will end his attack animation 
    {
        if (state == ATTACK)
        {
            al_draw_bitmap_region(autoattack_animation.texture, autoattack_animation.frame.p.x, autoattack_animation.frame.p.y,
                autoattack_animation.frame.w, autoattack_animation.frame.h, boundary.p.x, boundary.p.y, NULL);

            if (autoattack_animation.frame.p.x == 0)
            {
                
                ALLEGRO_BITMAP* bullet = al_load_bitmap("bullet.png");

                std::pair<int, int> c = move_coords(dir, range / 2);
                int x_ = boundary.p.x + c.first, y_ = boundary.p.y + c.second;

                al_draw_bitmap(bullet, x_, y_, NULL);
                al_destroy_bitmap(bullet);
            }

            autoattack_animation.frame.p.x += autoattack_animation.frame.w;
            if (autoattack_animation.frame.p.x >= COUNT_OF_FRAMES_AA * autoattack_animation.frame.w)
            {
                state = IDLE;
            }
            return;
        }
        if (state == IDLE)
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
        if (frozen != 0)
            --frozen;
    }


    //  uncomment to check movement
    /*virtual Ability spec1()
    {
        return Ability(Rect(), Texture("a.png"), 1, 1, 1);
    }
    virtual Ability spec2() 
    {
        return Ability(Rect(), Texture("a.png"), 1, 1, 1);
    }*/
};