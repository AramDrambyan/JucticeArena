#pragma once
#include "RangeHero.h"
#include "CaitlynDefines.h"

struct Caitlyn : public RangeHero
{
    Caitlyn(const Rect& r, Direction dir = UP, State state = IDLE)
        : RangeHero(r, Texture("caitlyn.png", Point(), COUNT_OF_FRAMES, COUNT_OF_FRAMES),
        Texture("caitlyn_attack.png", Point(), COUNT_OF_FRAMES_AA, COUNT_OF_FRAMES), "caitlyn",
        CT_MOVE_SPEED, CT_HEALTH, CT_DAMAGE, CT_RANGE, CT_AUTOATTACK_SPEED,
        CT_SPEC1_COOLDOWN, CT_SPEC2_COOLDOWN, SoundEffect("ct_range_attack.wav"), dir, state)
    {
        max_health = CT_HEALTH;
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

    virtual ~Caitlyn() {}

    virtual void draw() //  if state == ATTACK he will end his attack animation 
    {
        if (state == ATTACK)
        {
            al_draw_bitmap_region(autoattack_animation.texture, autoattack_animation.frame.p.x, autoattack_animation.frame.p.y,
                autoattack_animation.frame.w, autoattack_animation.frame.h, boundary.p.x, boundary.p.y, NULL);

            if (autoattack_animation.frame.p.x == 0)
            {

                ALLEGRO_BITMAP* bullet = al_load_bitmap("bullet.png");

                std::pair<int, int> c = move_coords(dir, 100);
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
    virtual Ability spec1(Hero& h)
    {
        if (frozen <= 0 && spec1_state == 0)
        {
            state = IDLE;
            spec1_state = spec1_cooldown;

            std::pair<int, int> c = move_coords(dir, 50);
            Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 50);
            return Ability(r, Texture("caitlyn_trap.png"), CT_TRAP_MOVE_SPEED, CT_TRAP_DAMAGE, CT_TRAP_TIME);
        }

        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual Ability spec1(Hero& h1, Hero& h2)
    {
        if (frozen <= 0 && spec1_state == 0)
        {
            state = IDLE;
            spec1_state = spec1_cooldown;

            std::pair<int, int> c = move_coords(dir, 50);
            Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 50);
            return Ability(r, Texture("caitlyn_trap.png"), CT_TRAP_MOVE_SPEED, CT_TRAP_DAMAGE, CT_TRAP_TIME);
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

            std::pair<int, int> c = move_coords(dir, 50);
            Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 50);
            if (dir == LEFT)
            {
                return Ability(r, Texture("caitlyn_rocket_left.png"),
					CT_ROCKET_MOVE_SPEED, CT_ROCKET_DAMAGE, CT_ROCKET_TIME, SoundEffect("hit-ability.wav"), dir);
            }
            if (dir == RIGHT)
            {
                return Ability(r, Texture("caitlyn_rocket_right.png"),
					CT_ROCKET_MOVE_SPEED, CT_ROCKET_DAMAGE, CT_ROCKET_TIME, SoundEffect("hit-ability.wav"), dir);
            }
            if (dir == UP)
            {
                return Ability(r, Texture("caitlyn_rocket_up.png"),
					CT_ROCKET_MOVE_SPEED, CT_ROCKET_DAMAGE, CT_ROCKET_TIME, SoundEffect("hit-ability.wav"), dir);
            }
            
            return Ability(r, Texture("caitlyn_rocket_down.png"),
				CT_ROCKET_MOVE_SPEED, CT_ROCKET_DAMAGE, CT_ROCKET_TIME, SoundEffect("hit-ability.wav"), dir);
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

			std::pair<int, int> c = move_coords(dir, 50);
			Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 50);
			if (dir == LEFT)
			{
				return Ability(r, Texture("caitlyn_rocket_left.png"),
					CT_ROCKET_MOVE_SPEED, CT_ROCKET_DAMAGE, CT_ROCKET_TIME, SoundEffect("hit-ability.wav"), dir);
			}
			if (dir == RIGHT)
			{
				return Ability(r, Texture("caitlyn_rocket_right.png"),
					CT_ROCKET_MOVE_SPEED, CT_ROCKET_DAMAGE, CT_ROCKET_TIME, SoundEffect("hit-ability.wav"), dir);
			}
			if (dir == UP)
			{
				return Ability(r, Texture("caitlyn_rocket_up.png"),
					CT_ROCKET_MOVE_SPEED, CT_ROCKET_DAMAGE, CT_ROCKET_TIME, SoundEffect("hit-ability.wav"), dir);
			}

			return Ability(r, Texture("caitlyn_rocket_down.png"),
				CT_ROCKET_MOVE_SPEED, CT_ROCKET_DAMAGE, CT_ROCKET_TIME, SoundEffect("hit-ability.wav"), dir);
		}
		return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
	}
    virtual void passive(Hero& h)
    {
        if (health <= CT_HEALTH / 2 && damage == CT_DAMAGE)
        {
            damage = CT_CRIT_DAMAGE;
        }
    }
    virtual void passive(Hero& h1, Hero& h2)
    {
        if (health <= CT_HEALTH / 2 && damage == CT_DAMAGE)
        {
            damage = CT_CRIT_DAMAGE;
        }
    }
};