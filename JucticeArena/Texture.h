#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

struct Texture
{
	Texture(const char* path_to_texture, Point p = Point(), double wp = 0, double hp = 0)	
	{
		texture = al_load_bitmap(path_to_texture);
		frame.p = p;
		frame.w = al_get_bitmap_width(texture) / wp;
		frame.h = al_get_bitmap_height(texture) / hp;
	}

    Texture() {}

	ALLEGRO_BITMAP* texture;
	Rect frame;


};
