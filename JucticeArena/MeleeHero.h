#pragma once
#include "Hero.h"

struct MeleeHero : public Hero
{
	MeleeHero(const Rect& r, const Texture& texture, const Texture& autoattack_animation, std::string name,
		int move_speed, int health, int damage, int range, int autoattack_speed,
        int spec1_cooldown, int spec2_cooldown, Direction dir = UP, State state = IDLE)
        : Hero(r, texture, autoattack_animation, name, move_speed, health, damage, range, autoattack_speed,
        spec1_cooldown, spec2_cooldown, dir, state) 
    {
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

	virtual bool is_able_to_attack(const Hero& h)
	{
		if (boundary.intersect_direction(h.boundary, dir) && autoattack_state == 0 && frozen == 0)
		{
			return true;
		}
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
        if (frozen != 0)
            --frozen;
    }

	virtual ~MeleeHero() {}
};