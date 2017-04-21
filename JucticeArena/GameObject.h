#pragma once
#include "Geometry.h"
#include "Texture.h"

struct GameObject
{
	Rect boundary;
	Texture texture;

	GameObject(const Rect& r, const Texture& texture)
		:boundary(r), texture(texture) {}

	virtual ~GameObject(){}

	virtual void draw() = 0;
};