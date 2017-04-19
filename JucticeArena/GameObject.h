#pragma once
#include "Geometry.h"
#include "Texture.h"

struct GameObject
{
	Rectangle boundary;
	Texture texture;

	GameObject(const Rectangle& r, const Texture& texture)
		:boundary(r), texture(texture) {}

	virtual ~GameObject(){}

	virtual void draw() = 0;
};