#pragma once
#include "Ability.h"

struct Hero : public MovableGameObject 
{
	Hero(const Rect& r, const Texture& texture, const Texture& autoattack_animation,
		int move_speed, int health, int damage,int autoattack_speed, int spec1_cooldown,
        int spec2_cooldown, Direction dir = DOWN, State state = IDLE)
		: MovableGameObject(r, texture, move_speed, damage, dir), health(health),
        spec1_cooldown(spec1_cooldown), spec2_cooldown(spec2_cooldown), 
        autoattack_speed(autoattack_speed), state(state), autoattack_animation(autoattack_animation)
    {
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

	virtual ~Hero() {}
    
    int frozen;
	int health;
	int autoattack_speed;
    int spec1_cooldown;
    int spec2_cooldown;

    int autoattack_state;
    int spec1_state;
    int spec2_state;

	State state;
	Texture autoattack_animation;

	virtual Ability spec1() = 0;
	virtual Ability spec2() = 0;
	virtual void autoattack(Hero&) = 0;
	virtual bool is_able_to_attack(const Hero&) = 0;

    void move(const Direction dir_)
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

            std::pair<int, int> c = move_coords(dir, move_speed);
            boundary.p.x += c.first;
            boundary.p.y += c.second;
        }
    }
};