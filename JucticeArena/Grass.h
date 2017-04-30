#pragma once

#include "GameObject.h"

struct Grass : public GameObject
{
    Grass(const Rect& r)
        : GameObject(r, Texture("grass.png")){}

    Grass() {}

    virtual void draw()
    {
        al_draw_bitmap(texture.texture, boundary.p.x, boundary.p.y, NULL);
    }

    virtual ~Grass() {}
};