#pragma once
#include "Ability.h"
#include <string>

struct Hero : public MovableGameObject 
{
	Hero(const Rect& r, const Texture& texture, const Texture& autoattack_animation, std::string name,
		int move_speed, int health, int damage, int range, int autoattack_speed, int spec1_cooldown,
        int spec2_cooldown, Direction dir = UP, State state = IDLE)
		: MovableGameObject(r, texture, move_speed, damage, dir), name(name), health(health),
        spec1_cooldown(spec1_cooldown), spec2_cooldown(spec2_cooldown), 
        autoattack_speed(autoattack_speed), state(state), autoattack_animation(autoattack_animation), range(range)
    {
        autoattack_state = 0;
        spec1_state = 0;
        spec2_state = 0;
        frozen = 0;
    }

	virtual ~Hero() {}
    
    std::string name;

    int frozen;
	int health;
	int autoattack_speed;
    int spec1_cooldown;
    int spec2_cooldown;
    int range;

    int autoattack_state;
    int spec1_state;
    int spec2_state;

	State state;
	Texture autoattack_animation;

    virtual void move(Direction) = 0;
	virtual Ability spec1(Hero&) = 0;
	virtual Ability spec2(Hero&) = 0;
	virtual void autoattack(Hero&) = 0;
	virtual bool is_able_to_attack(const Hero&) = 0;
};