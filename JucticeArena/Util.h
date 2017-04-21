#pragma once
#include <iostream>
#include "Enums.h"

std::pair<int, int> move_coords(Direction dir, int move_speed)
{
	if(dir == LEFT)
	{
		return std::make_pair(-move_speed, 0);
	}
	if(dir == RIGHT)
	{
		return std::make_pair(move_speed, 0);
	}
	if(dir == UP)
	{
		return std::make_pair(0, -move_speed);
	}
	if(dir == DOWN)
	{
		return std::make_pair(0, move_speed);
	}
}