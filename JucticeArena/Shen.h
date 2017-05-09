#pragma once
#include "MeleeHero.h"
#include "ShenDefines.h"

struct Shen : public MeleeHero
{
    Shen(const Rect& r, Direction dir = UP, State state = IDLE)
        : MeleeHero(r, Texture("shen.png", Point(), COUNT_OF_FRAMES, COUNT_OF_FRAMES),
        Texture("shen_attack.png", Point(), COUNT_OF_FRAMES_AA, COUNT_OF_FRAMES), "shen",
        SH_MOVE_SPEED, SH_HEALTH, SH_DAMAGE, SH_RANGE, SH_AUTOATTACK_SPEED,
        SH_SPEC1_COOLDOWN, SH_SPEC2_COOLDOWN, SoundEffect("melee_attack.wav"), dir, state)
    {
        max_health = SH_HEALTH;
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

    virtual ~Shen() {}

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
    virtual Ability spec1(Hero& h1, Hero& h2)
    {
        if (frozen <= 0 && spec1_state == 0)
        {
            state = IDLE;

            for (int i = 3; i >= 1; --i)
            {
                std::pair<int, int> c = move_coords(dir, 50 * i);
                int x = boundary.p.x + c.first;
                int y = boundary.p.y + c.second;
                Rect r = Rect(Point(x, y), boundary.w, boundary.h);
                if ((h1.boundary.intersects_rect(r) || h2.boundary.intersects_rect(r)) && !hit_wall(r) && !hit_water(r) && in_range(r))
                {
                    boundary = r;
                    spec1_state = spec1_cooldown;
                    break;
                }
            }
        }

        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
	virtual Ability spec2(Hero& h1, Hero& h2)
	{ 
		if (frozen <= 0 && spec2_state == 0)
		{
			state = ATTACK;
			autoattack_animation.frame.p.x = 0;
			autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

			spec2_state = spec2_cooldown;
			std::pair<int, int> c = move_coords(dir, SH_SHURIKEN_SIZE);
			return Ability(Rect(Point(boundary.p.x + c.first, boundary.p.y + c.second), SH_SHURIKEN_SIZE, SH_SHURIKEN_SIZE),
				Texture("shen_shuriken.png"), SH_SHURIKEN_MOVE_SPEED, SH_SHURIKEN_DAMAGE, SH_SHURIKEN_TIME, 
				SoundEffect("hit-ability.wav"), dir);
		}
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
    virtual Ability spec2(Hero& h)
    {
        if (frozen <= 0 && spec2_state == 0)
        {
            state = ATTACK;
            autoattack_animation.frame.p.x = 0;
            autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;

            spec2_state = spec2_cooldown;
            std::pair<int, int> c = move_coords(dir, SH_SHURIKEN_SIZE);
            return Ability(Rect(Point(boundary.p.x + c.first, boundary.p.y + c.second), SH_SHURIKEN_SIZE, SH_SHURIKEN_SIZE),
				Texture("shen_shuriken.png"), SH_SHURIKEN_MOVE_SPEED, SH_SHURIKEN_DAMAGE, SH_SHURIKEN_TIME,
				SoundEffect("hit-ability.wav"), dir);
        }
        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual void passive(Hero& h) {}
    virtual void passive(Hero& h1, Hero& h2) {}
};