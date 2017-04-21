#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_image.h>

struct Texture
{
	Texture(const char* path_to_texture, Point p = Point())	
	{
		texture = al_load_bitmap(path_to_texture);
		frame.p = p;
		frame.w = al_get_bitmap_width(texture) / 5;
		frame.h = al_get_bitmap_height(texture) / 4;
	}

	ALLEGRO_BITMAP* texture;
	Rect frame;

	void destroy()
	{
		al_destroy_bitmap(texture);
	}
};
