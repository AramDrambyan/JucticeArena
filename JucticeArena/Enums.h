#pragma once
#include <vector>

#define COUNT_OF_FRAMES 4
#define COUNT_OF_FRAMES_AA 3

enum Direction
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3,
};

enum State
{
	IDLE,
	MOVE,
	ATTACK,
};