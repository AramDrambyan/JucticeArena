#pragma once
#include "RangeHero.h"
#include "KarmaDefines.h"

struct Karma : public RangeHero
{
    Karma(const Rect& r, Direction dir = UP, State state = IDLE)
        : RangeHero(r, Texture("karma.png", Point(), COUNT_OF_FRAMES, COUNT_OF_FRAMES),
        Texture("karma_attack.png", Point(), COUNT_OF_FRAMES_AA, COUNT_OF_FRAMES), "LeBlanc",
        K_MOVE_SPEED, K_HEALTH, K_DAMAGE, K_RANGE, K_AUTOATTACK_SPEED,
        K_SPEC1_COOLDOWN, K_SPEC2_COOLDOWN, SoundEffect("range_attack.wav"), dir, state)
    {
        max_health = K_HEALTH;
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

    virtual ~Karma() {}

    virtual void draw() //  if state == ATTACK he will end his attack animation 
    {
        if (state == ATTACK)
        {
            al_draw_bitmap_region(autoattack_animation.texture, autoattack_animation.frame.p.x, autoattack_animation.frame.p.y,
                autoattack_animation.frame.w, autoattack_animation.frame.h, boundary.p.x, boundary.p.y, NULL);

            if (autoattack_animation.frame.p.x == 0)
            {

                ALLEGRO_BITMAP* bullet = al_load_bitmap("k_sphere.png");

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

                if (!hit_wall(r) && in_range(r))
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

            health += K_HEAL;
            if (health > K_HEALTH)
            {
                health = K_HEALTH;
            }

            return Ability(Rect(Point(boundary.p.x - 25, boundary.p.y - 25), K_HEAL_SIZE, K_HEAL_SIZE),
                Texture("karma_heal.png"), K_HEAL_MOVE_SPEED, K_HEAL_DAMAGE, K_HEAL_TIME);
        }
        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);

    }
	virtual Ability spec2(Hero& h1, Hero& h2) 
	{
		if (frozen <= 0 && spec2_state == 0)
		{
			state = IDLE;
			spec2_state = spec2_cooldown;

			health += K_HEAL;
			if (health > K_HEALTH)
			{
				health = K_HEALTH;
			}

			return Ability(Rect(Point(boundary.p.x - 25, boundary.p.y - 25), K_HEAL_SIZE, K_HEAL_SIZE),
				Texture("karma_heal.png"), K_HEAL_MOVE_SPEED, K_HEAL_DAMAGE, K_HEAL_TIME);
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
            Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 50);
            return Ability(r, Texture("karma_fireball.png"),
				K_SPHERE_MOVE_SPEED, K_SPHERE_DAMAGE, K_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir);

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
            Rect r(Point(boundary.p.x + c.first, boundary.p.y + c.second), 50, 50);
            return Ability(r, Texture("karma_fireball.png"),
				K_SPHERE_MOVE_SPEED, K_SPHERE_DAMAGE, K_SPHERE_TIME, SoundEffect("hit-ability.wav"), dir);

        }
        return Ability(Rect(Point(-1, -1)), Texture("wall.png"), 0, 0, 0);
    }
    virtual void passive(Hero& h) {}
    virtual void passive(Hero& h1, Hero& h2) {}
};