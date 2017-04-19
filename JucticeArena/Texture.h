#pragma once
#include <string>

struct Texture
{
	Texture(const std::string& path_to_texture)
		: path_to_texture(path_to_texture) {}

	std::string path_to_texture;
	int frame;
	// TODO: add conversion to allegro here
	// bitmap get_allegro_bitmap() {  }
};