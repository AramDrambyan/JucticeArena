#pragma once
#include "MeleeHero.h"
#include "ShenDefines.h"

struct Shen : public MeleeHero
{
    Shen(const Rect& r, Direction dir = UP, State state = IDLE)
        : MeleeHero(r, Texture("shen.png", Point(), COUNT_OF_FRAMES, COUNT_OF_FRAMES),
        Texture("shen_attack.png", Point(), COUNT_OF_FRAMES_AA, COUNT_OF_FRAMES), "shen",
        MOVE_SPEED, HEALTH, DAMAGE, RANGE, AUTOATTACK_SPEED,
        SPEC1_COOLDOWN, SPEC2_COOLDOWN, dir, state)
    {
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

    virtual ~Shen() {}

    virtual void move(const Direction dir_)
    {
        if (frozen == 0)
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
        if (frozen == 0 && spec1_state == 0)
        {
            state = IDLE;

            for (int i = 3; i >= 1; --i)
            {
                std::pair<int, int> c = move_coords(dir, 50 * i);
                int x = boundary.p.x + c.first;
                int y = boundary.p.y + c.second;
                Rect r = Rect(Point(x, y), boundary.w, boundary.h);
                if (h.boundary.intersects_rect(r) && !hit_wall(r) && !hit_water(r) && in_range(r))
                {
                    boundary = r;
                    spec1_state = spec1_cooldown;
                    break;
                }
            }
        }

        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual Ability spec2(Hero& h)
    {
        if (frozen == 0 && spec2_state == 0)
        {
            state = ATTACK;
            autoattack_animation.frame.p.x = 0;
            autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

            spec2_state = spec2_cooldown;
            std::pair<int, int> c = move_coords(dir, SHURIKEN_SIZE);
            return Ability(Rect(Point(boundary.p.x + c.first, boundary.p.y + c.second), SHURIKEN_SIZE, SHURIKEN_SIZE),
                Texture("shuriken.png"), SHURIKEN_RANGE, SHURIKEN_MOVE_SPEED, SHURIKEN_DAMAGE, dir);
        }
        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
};