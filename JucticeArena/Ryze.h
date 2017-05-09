#pragma once
#include "RangeHero.h"
#include "RyzeDefines.h"

struct Ryze : public RangeHero
{
    Ryze(const Rect& r, Direction dir = UP, State state = IDLE)
        : RangeHero(r, Texture("ryze.png", Point(), COUNT_OF_FRAMES, COUNT_OF_FRAMES),
        Texture("ryze_attack.png", Point(), COUNT_OF_FRAMES_AA, COUNT_OF_FRAMES), "caitlyn",
        R_MOVE_SPEED, R_HEALTH, R_DAMAGE, R_RANGE, R_AUTOATTACK_SPEED,
        R_SPEC1_COOLDOWN, R_SPEC2_COOLDOWN, SoundEffect("range_attack.wav"), dir, state)
    {
        max_health = R_HEALTH;
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

    virtual ~Ryze() {}

    virtual void draw() //  if state == ATTACK he will end his attack animation 
    {
        if (state == ATTACK)
        {
            al_draw_bitmap_region(autoattack_animation.texture, autoattack_animation.frame.p.x, autoattack_animation.frame.p.y,
                autoattack_animation.frame.w, autoattack_animation.frame.h, boundary.p.x, boundary.p.y, NULL);

            if (autoattack_animation.frame.p.x == 0)
            {

                ALLEGRO_BITMAP* bullet = al_load_bitmap("r_sphere.png");

                std::pair<int, int> c = move_coords(dir, 75);
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

        if (autoattack_state > 0)
            --autoattack_state;
        if (spec1_state > 0)
            --spec1_state;
        if (spec2_state > 0)
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
    virtual Ability spec2(Hero& h)
    {
        if (frozen <= 0 && spec2_state == 0)
        {
            state = IDLE;
            spec2_state = spec2_cooldown;

            frozen = R_TP_WAITING;

            Rect r(Point(550, 350), R_TP_SIZE, R_TP_SIZE);
            return Ability(r, Texture("ryze_tp.png"), R_TP_MOVE_SPEED, R_TP_DAMAGE, R_TP_TIME);
        }

        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual Ability spec1(Hero& h)
    {
        if (frozen <= 0 && spec1_state == 0)
        {
            state = ATTACK;
            autoattack_animation.frame.p.x = 0;
            autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;
            spec1_state = spec1_cooldown;

            std::pair<int, int> c = move_coords(dir, 50);
            if (dir == LEFT)
            {
                Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 100, 50);
                return Ability(r, Texture("ryze_sphere_left.png"),
                    R_SPHERE_MOVE_SPEED, R_SPHERE_DAMAGE, R_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir, R_SPHERE_FROZE_TIME);
            }
            if (dir == RIGHT)
            {
                Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 100, 50);
                return Ability(r, Texture("ryze_sphere_right.png"),
                    R_SPHERE_MOVE_SPEED, R_SPHERE_DAMAGE, R_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir, R_SPHERE_FROZE_TIME);
            }
            if (dir == UP)
            {
                Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 100);
                return Ability(r, Texture("ryze_sphere_up.png"),
                    R_SPHERE_MOVE_SPEED, R_SPHERE_DAMAGE, R_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir, R_SPHERE_FROZE_TIME);
            }

            Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 100);
            return Ability(r, Texture("ryze_sphere_down.png"),
                R_SPHERE_MOVE_SPEED, R_SPHERE_DAMAGE, R_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir, R_SPHERE_FROZE_TIME);
        }
        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual Ability spec1(Hero& h1, Hero& h2)
    {
        if (frozen <= 0 && spec1_state == 0)
        {
            state = ATTACK;
            autoattack_animation.frame.p.x = 0;
            autoattack_animation.frame.p.y = dir * autoattack_animation.frame.h;
            spec1_state = spec1_cooldown;

            std::pair<int, int> c = move_coords(dir, 50);
            if (dir == LEFT)
            {
                Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 100, 50);
                return Ability(r, Texture("ryze_sphere_left.png"),
					R_SPHERE_MOVE_SPEED, R_SPHERE_DAMAGE, R_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir, R_SPHERE_FROZE_TIME);
            }
            if (dir == RIGHT)
            {
                Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 100, 50);
                return Ability(r, Texture("ryze_sphere_right.png"),
					R_SPHERE_MOVE_SPEED, R_SPHERE_DAMAGE, R_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir, R_SPHERE_FROZE_TIME);
            }
            if (dir == UP)
            {
                Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 100);
                return Ability(r, Texture("ryze_sphere_up.png"),
					R_SPHERE_MOVE_SPEED, R_SPHERE_DAMAGE, R_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir, R_SPHERE_FROZE_TIME);
            }

            Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 100);
            return Ability(r, Texture("ryze_sphere_down.png"),
				R_SPHERE_MOVE_SPEED, R_SPHERE_DAMAGE, R_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir, R_SPHERE_FROZE_TIME);
        }
        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
	virtual Ability spec2(Hero& h1, Hero& h2)
	{
		if (frozen <= 0 && spec2_state == 0)
		{
			state = IDLE;
			spec2_state = spec2_cooldown;

			frozen = R_TP_WAITING;

			Rect r(Point(550, 350), R_TP_SIZE, R_TP_SIZE);
			return Ability(r, Texture("ryze_tp.png"), R_TP_MOVE_SPEED, R_TP_DAMAGE, R_TP_TIME);
		}

		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
    virtual void passive(Hero& h)
    {
        if (spec1_state == spec1_cooldown && spec2_state >= R_PASSIVE)
        {
            spec2_state -= R_PASSIVE;
        }
        if (frozen == -5)
        {
            boundary.p.x = 575;
            boundary.p.y = 375;
        }
    }
    virtual void passive(Hero& h1, Hero& h2)
    {
        if (spec1_state == spec1_cooldown && spec2_state >= R_PASSIVE)
        {
            spec2_state -= R_PASSIVE;
        }
        if (frozen == -5)
        {
            boundary.p.x = 575;
            boundary.p.y = 375;
        }
    }
};